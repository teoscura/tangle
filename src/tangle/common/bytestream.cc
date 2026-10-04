#include <common/bytestream.hh>

#include <istream>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace tangle::common {

bytebuf::bytebuf
(uint8_t *buffer, size_t length)
{
    setg((char*)buffer, (char*)buffer, (char*)buffer+length);  
}

bebyteistream::bebyteistream
(uint8_t *buffer, size_t length)
: std::istream(&m_buffer),
m_buffer(buffer, length)
{
    rdbuf(&m_buffer);
}

bebyteistream& bebyteistream::operator>>
(std::string& value)
{
    int16_t len = 0;
    *this >> len;
    uint8_t dump = 0;
    std::stringstream ss;
    for(int i = 0; i < len; i++)
    {
        *this >> dump;
        *this >> dump;
        ss.put(dump);
    }
    value = ss.str();
    return *this;
}

bebyteostream::bebyteostream
(uint8_t *buffer, size_t length)
: m_buffer(buffer), m_length(length), m_index(0)
{}

bebyteostream& bebyteostream::operator<<
(const std::string& value)
{
    if(m_index + 2 >= m_length) throw std::runtime_error("Buffer overflow.");
    int16_t len = value.size();
    if(m_index + 2 * len >= m_length) throw std::runtime_error("Buffer overflow.");
    *this << len;
    uint8_t dump = 0;
    for(uint8_t e : value)
    {
        m_buffer[m_index++] = dump;
        m_buffer[m_index++] = e;
    }
    return *this;
}

std::vector<uint8_t> bebyteostream::getBytes
()
{
    std::vector<uint8_t> vec(m_buffer, m_buffer+m_index);
    return vec;
}

}