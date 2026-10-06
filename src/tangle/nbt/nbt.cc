#include "common/bytestream.hh"
#include <bit>
#include <cstdint>
#include <stack>
#include <memory>
#include <nbt/nbt.hh>

#include <endian.h>
#include <format>
#include <print>
#include <string>

namespace tangle::nbt {

nbt_tag::nbt_tag(tag_type type, std::string name)
: m_tag(type)
, m_name(name)
, m_payload(nullptr) {}


tag_type nbt_tag::get_type() const {
    return m_tag;
}

std::string nbt_tag::name() const {
    return m_name;
}

std::shared_ptr<nbt_payload> nbt_tag::payload() {
    return m_payload;
}

void nbt_tag::set(std::shared_ptr<nbt_payload> payload) {
    m_payload = payload;
}

void nbt_tag::serialize(std::vector<uint8_t>& vec) const {
    vec.reserve(vec.size() + m_name.length() + 3);
    common::bebyteostream str(vec.data()+vec.size(), vec.capacity()-vec.size());
    uint8_t tag = static_cast<uint8_t>(m_tag);
    str << tag;
    str << m_name;
    m_payload->serialize(vec);
}

nbt_string::nbt_string(std::string value)
: m_string(value) {}

std::string nbt_string::string() const {
    return m_string;
}

void nbt_string::serialize(std::vector<uint8_t>& buf) const {
    buf.reserve(buf.size() + m_string.length() + 2);
    common::bebyteostream str(buf.data()+buf.size(), buf.capacity()-buf.size());
    str << m_string;
}

nbt_string::~nbt_string() {}

nbt_list::nbt_list(tag_type type, std::vector<std::shared_ptr<nbt_payload>> contents)
: m_content_type(type)
, m_contents(contents) {}

tag_type nbt_list::get_type() const {
    return m_content_type;
}

std::vector<std::shared_ptr<nbt_payload>>& nbt_list::contents() {
    return m_contents;
}

void nbt_list::serialize(std::vector<uint8_t>& buf) const {
    buf.reserve(buf.size() + 3);
    common::bebyteostream str(buf.data()+buf.size(), buf.capacity()-buf.size());
    uint16_t len = m_contents.size();
    uint8_t tag = static_cast<uint8_t>(m_content_type);
    str << tag;
    str << len;
    for(const auto& ref : m_contents) {
        ref->serialize(buf);
    }
}

nbt_list::~nbt_list() {}

nbt_compound::nbt_compound(std::vector<nbt_tag> fields)
: m_original(fields) {
    for(auto& ref : fields) {
        if(m_fields.contains(ref.name())) throw std::format_error("double field name");
        m_fields.insert_or_assign(ref.name(), ref);
    }
}
std::vector<nbt_tag>& nbt_compound::fields() {
    return m_original;
}

nbt_tag nbt_compound::get_field(std::string name) {
    if(!m_fields.contains(name)) return nbt_tag(tag_type::nbt_end, "");
    auto tag = m_fields.at(name);
    return tag;
}

void nbt_compound::serialize(std::vector<uint8_t>& buf) const {
    buf.reserve(buf.size()+3*m_fields.size());
    for(const auto& ref : m_fields) {
        ref.second.serialize(buf);
    }
    buf.push_back(static_cast<uint8_t>(tag_type::nbt_end));
}

nbt_compound::~nbt_compound() {}

nbt_writer::nbt_writer(std::ofstream file)
: m_file(std::move(file)) {}
    
std::size_t nbt_writer::write(nbt_tag root) {
    std::vector<uint8_t> vec(0x1000);
    root.serialize(vec);
    m_file << vec.data();
    return vec.size();
}

int nbt_writer::close() {
    m_file.flush();
    m_file.close();
    return m_file.bad();
}

nbt_writer::~nbt_writer() {
    close();
}

nbt_reader::nbt_reader(std::ifstream file)
: m_file(std::move(file)) {}

nbt_tag nbt_reader::get_tag() {
    if(m_file.bad() || m_file.eof()) throw std::format_error("not enough data!");
    uint8_t type = 0;
    uint16_t name_len = 0;
    std::string name = "";
    m_file.read((char*)&type, 1);
    if(type != 0) {
        m_file.read((char*)&name_len, 2);
        name_len = be16toh(name_len);
        name.reserve(name_len);
        std::vector<uint8_t> data(name_len);
        m_file.read((char*)data.data(), name_len);
        name = std::string(data.data(), data.data()+name_len);
    }
    switch(static_cast<tag_type>(type)) {
        case tag_type::nbt_end:
        case tag_type::nbt_byte:
        case tag_type::nbt_short:
        case tag_type::nbt_int:
        case tag_type::nbt_long:
        case tag_type::nbt_float:
        case tag_type::nbt_double:
        case tag_type::nbt_barray:
        case tag_type::nbt_string:
        case tag_type::nbt_list:
        case tag_type::nbt_compound:
        case tag_type::nbt_iarray:
        case tag_type::nbt_larray:
            return nbt_tag(static_cast<tag_type>(type), name);
        default: throw std::format_error("invalid nbt tag");
    };
}

std::shared_ptr<nbt_payload> nbt_reader::get_payload(tag_type type) {
    if(m_file.bad() || m_file.eof()) throw std::format_error("not enough data!");
    std::shared_ptr<nbt_payload> payload = nullptr;
    switch(static_cast<tag_type>(type)) {
        case tag_type::nbt_end: {
        break;
    }
    case tag_type::nbt_byte: {
        uint8_t b;
        m_file.read((char*)&b, 1);
        payload = std::make_shared<nbt_numeric<uint8_t>>(b);
        break;
    }
    case tag_type::nbt_short: {
        uint16_t s;
        m_file.read((char*)&s, 2);
        s = be16toh(s);
        payload = std::make_shared<nbt_numeric<uint16_t>>(s);
        break;
    }
        case tag_type::nbt_int: {
        uint32_t i;
        m_file.read((char*)&i, 4);
        i = be32toh(i);
        payload = std::make_shared<nbt_numeric<uint32_t>>(i);
        break;
    }
    case tag_type::nbt_long: {
        uint64_t l;
        m_file.read((char*)&l, 8);
        l = be64toh(l);
        payload = std::make_shared<nbt_numeric<uint64_t>>(l);
        break;
    }
    case tag_type::nbt_float: {
        float f;
        m_file.read((char*)&f, 4);
        f = std::bit_cast<float>(std::byteswap(std::bit_cast<uint32_t>(f)));
        payload = std::make_shared<nbt_numeric<float>>(f);
        break;
    }
    case tag_type::nbt_double: {
        double f;
        m_file.read((char*)&f, 8);
        f = std::bit_cast<double>(std::byteswap(std::bit_cast<uint64_t>(f)));
        payload = std::make_shared<nbt_numeric<double>>(f);
        break;
    }
    case tag_type::nbt_string: {
        uint16_t str_len;
        m_file.read((char*)&str_len, 2);
        str_len = be16toh(str_len);
        std::vector<uint8_t> data(str_len);
        m_file.read((char*)data.data(), str_len);
        std::string str = std::string(data.data(), data.data()+str_len);
        payload = std::make_shared<nbt_string>(str);
        break;
    }
    case tag_type::nbt_list: {
        uint8_t tag;
        m_file.read((char*)&tag, 1);
        uint32_t list_len;
        m_file.read((char*)&list_len, 4);
        list_len = be32toh(list_len);
        std::vector<std::shared_ptr<nbt_payload>> vec;
        vec.reserve(list_len);
        for(std::size_t i = 0; i < list_len; i++) {
            vec.push_back(get_payload(static_cast<tag_type>(tag)));
        }
        payload = std::make_shared<nbt_list>(static_cast<tag_type>(tag), std::move(vec));
        break;
    }
    case tag_type::nbt_compound: {
        std::vector<nbt_tag> fields;
        nbt_tag read(tag_type::nbt_end, "");
        do {
            read = get_tag();
            auto payload = get_payload(read.get_type());
            if(payload != nullptr) read.set(payload);
            if(read.get_type() != tag_type::nbt_end) fields.push_back(read);
        } while(read.get_type() != tag_type::nbt_end);
        payload = std::make_shared<nbt_compound>(fields);
        break;
    }
    case tag_type::nbt_barray: {
        uint16_t arr_len; 
        m_file.read((char*)&arr_len, 2);
        arr_len = be16toh(arr_len);
        std::vector<uint8_t> arr;
        arr.reserve(arr_len);
        for(std::size_t i = 0; i < arr_len; i++) {
            uint8_t data;
            m_file.read((char*)&data, 1);
            arr.push_back(data);
        }
        payload = std::make_shared<nbt_array<uint8_t>>(std::move(arr));
        break;
    }
    case tag_type::nbt_iarray: {
        uint16_t arr_len; 
        m_file.read((char*)&arr_len, 2);
        arr_len = be16toh(arr_len);
        std::vector<uint32_t> arr;
        arr.reserve(arr_len);
        for(std::size_t i = 0; i < arr_len; i++) {
            uint32_t data;
            m_file.read((char*)&data, 4);
            data = be32toh(data);
            arr.push_back(data);
        }
        payload = std::make_shared<nbt_array<uint32_t>>(std::move(arr));
        break;
    }
    case tag_type::nbt_larray: {
        uint16_t arr_len; 
        m_file.read((char*)&arr_len, 2);
        arr_len = be16toh(arr_len);
        std::vector<uint64_t> arr;
        arr.reserve(arr_len);
        for(std::size_t i = 0; i < arr_len; i++) {
            uint64_t data;
            m_file.read((char*)&data, 64);
            data = be64toh(data);
            arr.push_back(data);
        }
        payload = std::make_shared<nbt_array<uint64_t>>(std::move(arr));
        break;
    }
    default:
        throw std::format_error("invalid nbt tag");
    }
    return payload;
}

nbt_tag nbt_reader::get_tree() {
    std::println("starting read");
    std::stack<nbt_tag> read;
    try {
        nbt_tag tag = get_tag();
        auto payload = get_payload(tag.get_type());
        tag.set(payload);
        return tag;
    } catch (std::format_error& e) {
        std::println("Something went wrong in parsing nbt file! {}", e.what());
    }
    return nbt_tag(tag_type::nbt_end, "");
}

int nbt_reader::close() {
    if(m_file.is_open()) {
        m_file.close();
    }
    return m_file.bad();
}

nbt_reader::~nbt_reader() {
    close();
}

};


