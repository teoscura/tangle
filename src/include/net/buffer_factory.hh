#ifndef TANGLE_NET_BUF_FACT_H
#define TANGLE_NET_BUF_FACT_H

#include <cstdint>
#include <deque>
#include <memory>
#include <mutex>
#include <vector>

namespace tangle::net {

template<typename T, typename AllocT = std::allocator<void>>
class buffer_factory : public std::enable_shared_from_this<buffer_factory<T, AllocT>> {
public:
    class value;

    using element_type = std::decay_t<T>;
    using value_type = value;

    using allocator_type = AllocT;

    static_assert(std::is_move_constructible_v<element_type>, "buffer_factory element type must be move constructible");

    explicit buffer_factory(const allocator_type & = allocator_type());

    buffer_factory(const buffer_factory &) = delete;

    buffer_factory(buffer_factory &&) = default;

    buffer_factory &operator=(const buffer_factory &) = delete;

    buffer_factory &operator=(buffer_factory &&) = default;

    std::size_t available() const;

    template<typename... ArgTs>
    value_type get_or(ArgTs &&...);

    void insert(const element_type & = element_type(), std::size_t = 1);

    template<typename U>
    void insert(U &&);

    template<typename... ArgTs>
    void emplace(ArgTs &&...args);

    void clear();

    allocator_type get_allocator() const {
        return alloc_;
    }

private:
    using element_allocator_type = typename std::allocator_traits<AllocT>::template rebind_alloc<element_type>;

    using element_ref_type = std::reference_wrapper<element_type>;
    using element_ref_allocator_type = typename std::allocator_traits<AllocT>::template rebind_alloc<element_ref_type>;

    void cache(element_type &);

    mutable std::mutex mx_;
    std::deque<element_type, element_allocator_type> cache_;
    std::deque<element_ref_type, element_ref_allocator_type> values_;

    allocator_type alloc_;
};

template<typename T, typename AllocT>
class buffer_factory<T, AllocT>::value {
public:
    value(const value &) = delete;

    value(value &&) = default;

    ~value();

    value &operator=(const value &) = delete;

    value &operator=(value &&) = default;

    element_type &get() { return element_; }

    const element_type &get() const { return element_; }

    element_type &operator*() { return get(); }

    const element_type &operator*() const { return get(); }

    element_type *operator->() { return &get(); }

    const element_type *operator->() const { return &get(); }

    operator element_type &() { return get(); }

    operator const element_type &() { return get(); }

    bool valid() const { return factory_ != nullptr; }

private:
    friend class buffer_factory;

    value(buffer_factory &, element_type &);

    std::shared_ptr<buffer_factory> factory_;
    std::reference_wrapper<element_type> element_;
};

template<typename T, typename AllocT>
buffer_factory<T, AllocT>::buffer_factory(const allocator_type &alloc)
    : cache_(element_allocator_type(alloc)),
      values_(element_ref_allocator_type(alloc)),
      alloc_(alloc) {
}

template<typename T, typename AllocT>
std::size_t buffer_factory<T, AllocT>::available() const {
    std::lock_guard lock(mx_);
    return values_.size();
}

template<typename T, typename AllocT>
template<typename... ArgTs>
auto buffer_factory<T, AllocT>::get_or(ArgTs &&...args) -> value_type {
    std::lock_guard lock(mx_);
    
    if (values_.empty()) {
        cache_.emplace_back(std::forward<ArgTs>(args)...);
        return value_type(*this, cache_.back());
    }

    const auto value = values_.back();
    values_.pop_back();

    return value_type(*this, value);
}

template<typename T, typename AllocT>
void buffer_factory<T, AllocT>::insert(const element_type &e, std::size_t count) {
    std::lock_guard lock(mx_);

    for (; count > 0; --count) {
        cache_.emplace_back(e);
        values_.emplace_back(cache_.back());
    }
}
template<typename T, typename AllocT>
template<typename U>
void buffer_factory<T, AllocT>::insert(U &&e) {
    std::lock_guard lock(mx_);

    cache_.emplace_back(std::forward<U>(e));
    values_.emplace_back(cache_.back());
}

template<typename T, typename AllocT>
template<typename... ArgTs>
void buffer_factory<T, AllocT>::emplace(ArgTs &&...args) {
    std::lock_guard lock(mx_);

    cache_.emplace_back(std::forward<ArgTs>(args)...);
    values_.emplace_back(cache_.back());
}

template<typename T, typename AllocT>
void buffer_factory<T, AllocT>::clear() {
    std::lock_guard lock(mx_);

    values_.clear();
    cache_.clear();
}

template<typename T, typename AllocT>
void buffer_factory<T, AllocT>::cache(element_type &e) {
    std::lock_guard lock(mx_);
    values_.emplace_back(e);
}

template<typename T, typename AllocT>
buffer_factory<T, AllocT>::value::value(buffer_factory &factory, element_type &element)
    : factory_(factory.shared_from_this()),
      element_(element) {
}

template<typename T, typename AllocT>
buffer_factory<T, AllocT>::value::~value() {
    if (factory_ != nullptr) {
        factory_->cache(element_);
    }
}

using buf_fac = buffer_factory<std::vector<uint8_t>>; 

}

#endif //TANGLE_NET_BUF_FACT_H