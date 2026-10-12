#include "net/client_descriptor.hh"
#include <net/packet/incoming_packet.hh>

namespace tangle::net::packet {

incoming_packet::incoming_packet(client_descriptor cd) 
: m_cd(cd) {}

incoming_packet::~incoming_packet(){}

user_ka_packet::user_ka_packet(client_descriptor cd)
: incoming_packet(cd) {}

void user_ka_packet::handle(packet_handler& handler) {
    (void) handler;
}

user_loginreq_packet::user_loginreq_packet(client_descriptor cd, bebyteistream& bstr) 
: incoming_packet(cd) {
    bstr >> m_ver;
    bstr >> m_username;
}

void user_loginreq_packet::handle(packet_handler& handler) {
    (void) handler;
}

user_hs_packet::user_hs_packet(client_descriptor cd, bebyteistream& bstr) 
: incoming_packet(cd) {
    bstr >> m_username;
}

void user_hs_packet::handle(packet_handler& handler) {
    (void) handler;
}

user_chat_packet::user_chat_packet(client_descriptor cd, bebyteistream& bstr) 
: incoming_packet(cd) {
    bstr >> m_message;
}

void user_chat_packet::handle(packet_handler& handler) {
    (void) handler;
}

user_grounded_packet::user_grounded_packet(client_descriptor cd, bebyteistream& bstr) 
: incoming_packet(cd) {
    bstr >> m_grounded;
}

void user_grounded_packet::handle(packet_handler& handler) {
    (void) handler;
}

user_pos_packet::user_pos_packet(client_descriptor cd, bebyteistream& bstr) 
: incoming_packet(cd) {
    bstr >> m_x;
    bstr >> m_y;
    bstr >> m_s;
    bstr >> m_z;
    bstr >> m_grounded;
}

void user_pos_packet::handle(packet_handler& handler) {
    (void) handler;
};

user_look_packet::user_look_packet(client_descriptor cd, bebyteistream& bstr)
: incoming_packet(cd) {
    bstr >> m_yaw;
    bstr >> m_pitch;
    bstr >> m_grounded;
}

void user_look_packet::handle(packet_handler& handler) {
    (void) handler;
};

user_pl_packet::user_pl_packet(client_descriptor cd, bebyteistream& bstr)
: incoming_packet(cd) {
    bstr >> m_x;
    bstr >> m_y;
    bstr >> m_s;
    bstr >> m_z;
    bstr >> m_yaw;
    bstr >> m_pitch;
    bstr >> m_grounded;
}

void user_pl_packet::handle(packet_handler& handler) {
    (void) handler;
};

user_kick_packet::user_kick_packet(client_descriptor cd, std::string message) 
: incoming_packet(cd) 
, m_message(message){}

user_kick_packet::user_kick_packet(client_descriptor cd, bebyteistream& bstr) 
: incoming_packet(cd) {
    bstr >> m_message;
}

void user_kick_packet::handle(packet_handler& handler) {
    (void) handler;
}

}