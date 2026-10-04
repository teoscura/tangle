#ifndef TANGLE_COMMON_BYTESTREAM_H
#define TANGLE_COMMON_BYTESTREAM_H

#include <cstdint>
#include <streambuf>
#include <istream>
#include <vector>

namespace tangle::common {

template<class T> concept Numeric = std::is_arithmetic_v<T>;

class bytebuf : public std::basic_streambuf<char>
{
    public:
        bytebuf(uint8_t *buffer, size_t length);
};

class bebyteistream : public std::istream
{  
        bytebuf m_buffer;
    public:
        bebyteistream(uint8_t *buffer, size_t length);
        template<Numeric T>
        bebyteistream& operator>>(T& value);
        bebyteistream& operator>>(std::string& value);
};

class bebyteostream
{  
        uint8_t *m_buffer;
        size_t m_length;
        size_t m_index;
    public:
        bebyteostream(uint8_t *buffer, size_t length);
        template<Numeric T>
        bebyteostream& operator<<(T& value);
        bebyteostream& operator<<(const std::string& value);
        std::vector<uint8_t> getBytes();
};

template<Numeric T>
bebyteistream& bebyteistream::operator>>
(T& value)
{
    for(int i = sizeof(value) - 1; i>=0; i--)
    {
        read((char*)&value+i,1);
    }
    return *this;
}

template<Numeric T> 
bebyteostream& bebyteostream::operator<<
(T& value)
{
    if(m_index + sizeof(value) >= m_length) throw std::runtime_error("Buffer overflow.");
    uint8_t *buf = (uint8_t*) &value;
    for(int i = sizeof(value) - 1; i >= 0; i--)
    {
        m_buffer[m_index++] = buf[i];
    }
    return *this;
}

}

#endif //TANGLE_COMMON_BYTESTREAM_H