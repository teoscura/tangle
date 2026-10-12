#ifndef TANGLE_NET_PACKET_INCOMING_H
#define TANGLE_NET_PACKET_INCOMING_H

#include <cstdint>
#include <string>

#include <common/bytestream.hh>
#include <net/client_descriptor.hh>

namespace tangle::net::packet {

using namespace common;

class packet_handler;

class incoming_packet {
    protected:
        client_descriptor m_cd;
    public:
        incoming_packet(client_descriptor cd);
        virtual void handle(packet_handler& handler) = 0;
        virtual ~incoming_packet();
};

class user_ka_packet : public incoming_packet{
    public:
        user_ka_packet(client_descriptor cd);
        void handle(packet_handler& handler) override;
};

class user_loginreq_packet : public incoming_packet {
        int32_t m_ver;
        std::string m_username;
    public:
        user_loginreq_packet(client_descriptor cd, bebyteistream& bstr);
        void handle(packet_handler& handler) override;
};

class user_hs_packet : public incoming_packet {
        std::string m_username;
    public:
        user_hs_packet(client_descriptor cd, bebyteistream& bstr);
        void handle(packet_handler& handler) override;
};

class user_chat_packet : public incoming_packet {
        std::string m_message;
    public:
        user_chat_packet(client_descriptor cd, bebyteistream& bstr);
        void handle(packet_handler& handler) override;
};

class user_grounded_packet : public incoming_packet {
        bool m_grounded;
    public:
        user_grounded_packet(client_descriptor cd, bebyteistream& bstr);
        void handle(packet_handler& handler) override;
};

class user_pos_packet : public incoming_packet {
        double m_x;
        double m_y;
        double m_s;
        double m_z;
        bool m_grounded;
    public:
        user_pos_packet(client_descriptor cd, bebyteistream& bstr);
        void handle(packet_handler& handler) override;
};

class user_look_packet : public incoming_packet {
        float m_yaw;
        float m_pitch;
        bool m_grounded;
    public:
        user_look_packet(client_descriptor cd, bebyteistream& bstr);
        void handle(packet_handler& handler) override;
};

class user_pl_packet : public incoming_packet {
        double m_x;
        double m_y;
        double m_s;
        double m_z;
        float m_yaw;
        float m_pitch;
        bool m_grounded;
    public:
        user_pl_packet(client_descriptor cd, bebyteistream& bstr);
        void handle(packet_handler& handler) override;
};

class user_kick_packet : public incoming_packet {
        std::string m_message;
    public:
        user_kick_packet(client_descriptor cd, std::string message);
        user_kick_packet(client_descriptor cd, bebyteistream& bstr);
        void handle(packet_handler& handler) override;
};

}

#endif //TANGLE_NET_PACKET_INCOMING_H