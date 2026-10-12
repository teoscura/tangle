#ifndef TANGLE_COMMON_QUEUE_H
#define TANGLE_COMMON_QUEUE_H

#include <condition_variable>
#include <deque>
#include <mutex>
#include <type_traits>
#include <vector>

namespace tangle::common {

template<typename T>
class queue {
    static_assert(std::is_move_constructible_v<T>, "T must be move constructible");
    static_assert(std::is_move_assignable_v<T>, "T must be move assignable");

    std::deque<T> m_queue;
    std::mutex m_mtx;
    std::condition_variable m_cv;
public:
    queue(std::size_t size);
    std::vector<T> pending();
    std::size_t size();
    void push(T&& data);
};

template<typename T>
queue<T>::queue(std::size_t size) 
: m_queue(size) {}

template<typename T>
std::vector<T> queue<T>::pending() {
    std::unique_lock<std::mutex> lck(m_mtx);
    if(m_queue.empty()) m_cv.wait(lck);
    std::vector<T> res(m_queue.size());
    while(!m_queue.empty()) {
        auto t = std::move(m_queue.front());
        m_queue.pop_front();
        res.push_back(std::move(t));
    }
    return res;
}

template<typename T>
std::size_t queue<T>::size() {
    std::unique_lock<std::mutex> lck(m_mtx);
    return m_queue.size();
}

template<typename T>
void queue<T>::push(T&& data) {
    std::unique_lock<std::mutex> lck(m_mtx);
    m_queue.push_back(std::move(data));
    m_cv.notify_all();
}

}

#endif //TANGLE_COMMON_QUEUE_H
