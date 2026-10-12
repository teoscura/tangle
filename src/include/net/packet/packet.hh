#ifndef TANGLE_NET_PACKET_H
#define TANGLE_NET_PACKET_H

#include <cstdint>
#include <vector>

#include <net/client_descriptor.hh>

namespace tangle::net::packet {

/*
 * Client bound packet.
 */
class packet {
        client_descriptor m_cd;
    protected:
        packet(client_descriptor cd);
        virtual std::vector<uint8_t> serialize() const = 0;
        client_descriptor getCD() const;
        virtual ~packet() = default;
};

}

#endif //TANGLE_NET_PACKET_H