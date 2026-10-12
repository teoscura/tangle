#ifndef TANGLE_NET_PACKET_DESERIALIZER_H
#define TANGLE_NET_PACKET_DESERIALIZER_H

#include <memory>

#include <common/bytestream.hh>
#include <net/client_descriptor.hh>
#include <net/packet/incoming_packet.hh>

namespace tangle::net::packet {

using namespace common;

class deserializer {
public:
    deserializer();
    std::unique_ptr<incoming_packet> deserialize(client_descriptor cd, bebyteistream& bestr) const;
};

}

#endif //TANGLE_NET_PACKET_DESERIALIZER_H

