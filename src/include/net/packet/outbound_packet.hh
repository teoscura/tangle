#ifndef TANGLE_NET_PACKET_OUTBOUND_H
#define TANGLE_NET_PACKET_OUTBOUND_H

#include <cstdint>
#include <string>
#include <vector>

#include <net/packet/packet.hh>
#include <net/client_descriptor.hh>

namespace tangle::net::packet {

class server_keepalive_packet : public packet {
    public:
        server_keepalive_packet(client_descriptor cd);
        std::vector<uint8_t> serialize() const;
};

class server_loginreq_packet : public packet {
        uint32_t m_eid;
        std::string m_username;
        uint64_t m_seed;
        uint8_t m_dimension;
    public:
        server_loginreq_packet(client_descriptor cd, uint32_t eid, std::string username, uint64_t seed, uint8_t dimension);
        std::vector<uint8_t> serialize() const;
};

class server_hs_packet : public packet {
        std::string m_response;
    public:
        server_hs_packet(client_descriptor cd, std::string response);
        std::vector<uint8_t> serialize() const;
};

class server_chat_packet : public packet {
        std::string m_message;
    public:
        server_chat_packet(client_descriptor cd, std::string message);
        std::vector<uint8_t> serialize() const;
};

class time_packet : public packet {
        uint64_t m_time;
    public: 
        time_packet(client_descriptor cd, uint64_t time);
        std::vector<uint8_t> serialize() const;
};

class sp_packet : public packet {
        int32_t m_x;
        int32_t m_y;
        int32_t m_z;
    public:
        sp_packet(client_descriptor cd, int32_t x, int32_t y, int32_t z);
        std::vector<uint8_t> serialize() const;
};

class server_pl_packet : public packet {
        double m_x;
        double m_stance;
        double m_y;
        double m_z;
        float m_yaw;
        float m_pitch;
        bool m_onground;
    public:
        server_pl_packet(client_descriptor cd, double x, double stance, double y, double z, float yaw, float pitch, bool onground);
        std::vector<uint8_t> serialize() const;
};

class namedentity_packet : public packet {
        int32_t m_eid;
        std::string m_name;
        int32_t m_x;
        int32_t m_y;
        int32_t m_z;
        int8_t m_yaw;
        int8_t m_pitch;
        uint16_t m_item;
    public:
        namedentity_packet(client_descriptor cd, int32_t eid, std::string name, int32_t x, int32_t y, int32_t z, int8_t yaw, int8_t pitch, uint16_t item);
        std::vector<uint8_t> serialize() const;
};

enum class preloadmode : uint8_t {
    LOAD = 1,
    UNLOAD = 0
};

class preload_packet : public packet {
        int32_t m_x;
        int32_t m_z;
        int8_t m_mode;
    public:
        preload_packet(client_descriptor cd, int32_t x, int32_t z, int8_t mode);
        std::vector<uint8_t> serialize() const;
};

class chunk_packet : public packet {
        int32_t m_x;
        int16_t m_y;
        int32_t m_z;
        int8_t m_sx;
        int8_t m_sy;
        int8_t m_sz;
        int32_t m_cs;
        uint8_t* m_cchunk;
    public:
        chunk_packet(client_descriptor cd, int32_t x, int16_t y, int32_t z, int8_t sx, int8_t sy, int8_t sz, int32_t cs, uint8_t *chunk);
        std::vector<uint8_t> serialize() const;
};

class mbchange_packet : public packet {
        int32_t m_cx;
        int32_t m_cz;
        int16_t m_as;
        std::vector<uint8_t> m_data;
    public:
        mbchange_packet(client_descriptor cd, int32_t m_cx, int32_t m_cz, int16_t m_as, std::vector<uint8_t> m_data);
        std::vector<uint8_t> serialize() const;
};

class server_kick_packet : public packet {
        std::string m_reason;
    public:
        server_kick_packet(client_descriptor cd, std::string reason);
        std::vector<uint8_t> serialize() const;
};

}

#endif //TANGLE_NET_PACKET_OUTBOUND_H