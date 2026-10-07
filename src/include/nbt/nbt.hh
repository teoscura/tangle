#ifndef TANGLE_NBT_H
#define TANGLE_NBT_H

#include <cstdint>
#include <endian.h>
#include <fstream>
#include <print>
#include <memory>
#include <unordered_map>

#include <common/bytestream.hh>

namespace tangle::nbt {

enum class tag_type : uint8_t {
    nbt_end = 0x00,
    nbt_byte,
    nbt_short,
    nbt_int,
    nbt_long,
    nbt_float,
    nbt_double,
    nbt_barray,
    nbt_string,
    nbt_list,
    nbt_compound, 
    nbt_iarray,
    nbt_larray,
};

class nbt_payload {
public:
    virtual std::size_t serialize(std::ofstream& str) const = 0;
    virtual ~nbt_payload() {};
};

class nbt_tag {
    tag_type m_tag;
    std::string m_name;
    std::shared_ptr<nbt_payload> m_payload;
public:
    nbt_tag(tag_type type, std::string name);
    nbt_tag(const nbt_tag& other) = default;
    nbt_tag& operator=(const nbt_tag& other) = default;
    tag_type get_type() const;
    std::string name() const;
    std::shared_ptr<nbt_payload> payload();
    void set(std::shared_ptr<nbt_payload> payload);
    std::size_t serialize(std::ofstream& buf) const;
};

template<common::Numeric T>
class nbt_numeric : public nbt_payload {
    T m_value;
public:
    nbt_numeric(T value)
    : m_value(value) {}

    T get_value() const {
        return m_value;
    }

    virtual std::size_t serialize(std::ofstream& str) const override {
        std::println("writing numeric payload of size {}", sizeof(T));
        auto b = (uint8_t*) &m_value;
        for(int i = sizeof(T) - 1; i >= 0 ; i--) {
            str.put(b[i]);
        }
        return sizeof(T);
    }

    virtual ~nbt_numeric() override {} 
};

template<common::Numeric T>
class nbt_array : public nbt_payload {
    std::vector<T> m_array;
public:
    nbt_array(std::vector<T>&& contents)
    : m_array(contents) {}

    std::vector<T>& contents() {
        return m_array;
    }

    virtual std::size_t serialize(std::ofstream& str) const override {
        std::println("writing numeric array payload of size/length {}/{}", sizeof(T), m_array.size());
        uint16_t size = htobe16(m_array.size());
        str.write((char*)&size, 2);
        for(const auto& ref : m_array) {
            auto b = (uint8_t*) &ref;
            for(int i = sizeof(T) - 1; i >= 0 ; i--) {
                str.put(b[i]);
            }
        }
        return 2 + sizeof(T) * m_array.size();
    }

    virtual ~nbt_array() override {} 
};

class nbt_string : public nbt_payload {
    std::string m_string;
public:
    nbt_string(std::string value);
    std::string string() const;
    virtual std::size_t serialize(std::ofstream& str) const override;
    virtual ~nbt_string() override;
};

class nbt_list : public nbt_payload {
    tag_type m_content_type;
    std::vector<std::shared_ptr<nbt_payload>> m_contents;
public:
    nbt_list(tag_type type, std::vector<std::shared_ptr<nbt_payload>> contents);
    tag_type get_type() const;
    std::vector<std::shared_ptr<nbt_payload>>& contents();
    virtual std::size_t serialize(std::ofstream& str) const override;
    virtual ~nbt_list() override;
};

class nbt_compound : public nbt_payload {
    std::unordered_map<std::string, nbt_tag&> m_fields;
    std::vector<nbt_tag> m_original;
public:
    nbt_compound(std::vector<nbt_tag> fields);
    std::vector<nbt_tag>& fields();
    nbt_tag get_field(std::string name);
    virtual std::size_t serialize(std::ofstream& str) const override;
    virtual ~nbt_compound() override;
};

class nbt_writer {
    std::ofstream m_file;
public:
    nbt_writer(std::ofstream file);
    std::size_t write(nbt_tag root);
    int close();
    ~nbt_writer();
};

class nbt_reader {
    int tabs;
    std::ifstream m_file;
public:
    nbt_reader(std::ifstream file);
    nbt_tag get_tag();
    std::shared_ptr<nbt_payload> get_payload(tag_type type);
    nbt_tag get_tree();
    int close();
    ~nbt_reader();
};

}

#endif //TANGLE_NBT_H