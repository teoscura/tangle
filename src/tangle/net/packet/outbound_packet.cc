#include <net/packet/outbound_packet.hh>

#include <vector>

#include <net/packet/packet.hh>
#include <common/bytestream.hh>

namespace tangle::net::packet {

using tangle::common::bebyteostream;

server_keepalive_packet::server_keepalive_packet(client_descriptor cd)
: packet(cd) {}

std::vector<uint8_t> server_keepalive_packet::serialize() const {
    std::vector<uint8_t> vec(1);
    vec[0] = 0x00;
    return vec;
}

server_loginreq_packet::server_loginreq_packet(client_descriptor cd, uint32_t eid, std::string username, uint64_t seed, uint8_t dimension)
: packet(cd)
, m_eid(eid)
, m_username(username)
, m_seed(seed)
, m_dimension(dimension){}

std::vector<uint8_t> server_loginreq_packet::serialize() const {
    uint8_t buf[0x1000] = {0};
    bebyteostream bstr(buf, 0x1000);
    uint8_t id = 0x01;
    bstr << id << m_eid << m_username << m_seed << m_dimension;
    return bstr.getBytes();
}

server_hs_packet::server_hs_packet(client_descriptor cd, std::string response)
: packet(cd)
, m_response(response) {}

std::vector<uint8_t> server_hs_packet::serialize() const {
    uint8_t buf[0x1000] = {0};
    bebyteostream bstr(buf, 0x1000);
    uint8_t id = 0x02;
    bstr << id << m_response;
    return bstr.getBytes();
}

server_chat_packet::server_chat_packet(client_descriptor cd, std::string message)
: packet(cd)
, m_message(message) {}

std::vector<uint8_t> server_chat_packet::serialize() const {
    uint8_t buf[0x1000] = {0};
    bebyteostream bstr(buf, 0x1000);
    uint8_t id = 0x03;
    bstr << id << m_message;
    return bstr.getBytes();
}


time_packet::time_packet (client_descriptor cd, uint64_t time)
: packet(cd)
, m_time(time) {}

std::vector<uint8_t> time_packet::serialize() const {
    uint8_t buf[0x1000] = {0};
    bebyteostream bstr(buf, 0x1000);
    uint8_t id = 0x04;
    bstr << id << m_time;
    return bstr.getBytes();
}

sp_packet::sp_packet(client_descriptor cd, int32_t x, int32_t y, int32_t z)
: packet(cd)
, m_x(x)
, m_y(y)
, m_z(z) {}
        
std::vector<uint8_t> sp_packet::serialize() const {
    uint8_t buf[0x1000] = {0};
    bebyteostream bstr(buf, 0x1000);
    uint8_t id = 0x06;
    bstr << id << m_x<< m_y << m_z;
    return bstr.getBytes();
}

server_pl_packet::server_pl_packet(client_descriptor cd, double x, double stance, double y, double z, float yaw, float pitch, bool onground)
: packet(cd)
, m_x(x)
, m_stance(stance)
, m_y(y)
, m_z(z)
, m_yaw(yaw)
, m_pitch(pitch)
, m_onground(onground) {}

std::vector<uint8_t> server_pl_packet::serialize() const {
    uint8_t buf[0x1000] = {0};
    bebyteostream bstr(buf, 0x1000);
    uint8_t id = 0x0D;
    bstr << id << m_x << m_stance << m_y << m_z << m_yaw << m_pitch << m_onground;
    return bstr.getBytes();
}

namedentity_packet::namedentity_packet(client_descriptor cd, int32_t eid, std::string name, int32_t x, int32_t y, int32_t z, int8_t yaw, int8_t pitch, uint16_t item)
: packet(cd)
, m_eid(eid)
, m_name(name)
, m_x(x)
, m_y(y)
, m_z(z)
, m_yaw((yaw/360.0)*255.0)
, m_pitch((pitch/360.0)*255.0)
, m_item(item) {}

std::vector<uint8_t> namedentity_packet::serialize() const {
    uint8_t buf[0x1000] = {0};
    bebyteostream bstr(buf, 0x1000);
    uint8_t id = 0x14;
    bstr << id << m_eid << m_name << m_x << m_y << m_z << m_yaw << m_pitch << m_item;
    return bstr.getBytes();
}

preload_packet::preload_packet(client_descriptor cd, int32_t x, int32_t z, int8_t mode)
: packet(cd)
, m_x(x)
, m_z(z)
, m_mode(mode) {}

std::vector<uint8_t> preload_packet::serialize() const {
    uint8_t buf[0x1000] = {0};
    bebyteostream bstr(buf, 0x1000);
    uint8_t id = 0x32;
    bstr << id << m_x << m_z << m_mode;
    return bstr.getBytes();
}

chunk_packet::chunk_packet(client_descriptor cd, int32_t x, int16_t y, int32_t z, int8_t sx, int8_t sy, int8_t sz, int32_t cs, uint8_t *data)
: packet(cd)
, m_x(x)
, m_y(y)
, m_z(z)
, m_sx(sx)
, m_sy(sy)
, m_sz(sz)
, m_cs(cs)
, m_cchunk(data) {}

std::vector<uint8_t> chunk_packet::serialize() const {
    uint8_t buf[0x1000] = {0};
    bebyteostream bstr(buf, 0x1000);
    uint8_t id = 0x33;
    bstr << id << m_x << m_y << m_z << m_sx << m_sy << m_sz << m_cs;
    auto data = bstr.getBytes();
    data.insert(data.end(), m_cchunk, m_cchunk+m_cs);
    return data;
}

mbchange_packet::mbchange_packet(client_descriptor cd, int32_t cx, int32_t cz, int16_t sz, std::vector<uint8_t> data)
: packet(cd)
, m_cx(cx)
, m_cz(cz)
, m_as(sz)
, m_data(data) {}

std::vector<uint8_t> mbchange_packet::serialize() const{
    uint8_t buf[0x1000] = {0};
    bebyteostream bstr(buf, 0x1000); 
    uint8_t id = 0x34;
    bstr << id << m_cx << m_cz << m_as;
    auto data = bstr.getBytes();
    data.insert(data.end(), m_data.begin(), m_data.end());
    return data;
}

server_kick_packet::server_kick_packet(client_descriptor cd, std::string reason)
: packet(cd)
, m_reason(reason) {}

std::vector<uint8_t> server_kick_packet::serialize() const {
    uint8_t buf[0x1000] = {0};
    bebyteostream bstr(buf, 0x1000);
    uint8_t id = 0xFF;
    bstr << id << m_reason;
    return bstr.getBytes();
} 
    
}