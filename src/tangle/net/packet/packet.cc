#include <net/packet/packet.hh>

namespace tangle::net::packet {

packet::packet(client_descriptor cd)
: m_cd(cd){}

client_descriptor packet::getCD() const {
    return m_cd;
}

}


