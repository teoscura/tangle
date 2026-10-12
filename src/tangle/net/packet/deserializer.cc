#include "net/client_descriptor.hh"
#include <net/packet/deserializer.hh>

#include <net/packet/incoming_packet.hh>

namespace tangle::net::packet {

deserializer::deserializer() {}

std::unique_ptr<incoming_packet> deserializer::deserialize(client_descriptor cd, bebyteistream& bestr) const {
    uint8_t id = 0;
    bestr >> id;
    switch(id)
    {
        case 0x00:
            return std::make_unique<user_ka_packet>(cd);
        case 0x01:
            return std::make_unique<user_loginreq_packet>(cd, bestr);
        case 0x02:
            return std::make_unique<user_hs_packet>(cd, bestr);
        case 0x03:
            return std::make_unique<user_chat_packet>(cd, bestr);
        case 0x0A:
            return std::make_unique<user_grounded_packet>(cd, bestr);
        case 0x0B:
            return std::make_unique<user_pos_packet>(cd, bestr);
        case 0x0C:
            return std::make_unique<user_look_packet>(cd, bestr);
        case 0x0D:
            return std::make_unique<user_pl_packet>(cd, bestr);
        case 0xFF:
            return std::make_unique<user_kick_packet>(cd, bestr);
        default:
            break;
    }
    return nullptr;
}

}