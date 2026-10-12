#include "net/client_descriptor.hh"
#include "outbound_packet.hh"
#include <cstdint>
#include <sys/socket.h>

#include <net/packet/outbound_packet.hh>

namespace tangle::net::packet {

inline void send_hsresp(client_descriptor fd) {
    uint8_t buf1[] = {0x02, 0x00, 0x01, 0x00, 0x2D};
    send(fd.fd, buf1, 5, 0);
}

inline void lastresp(client_descriptor fd) {
    uint8_t buf2[16] = {0};
    buf2[0] = 0x01;
    buf2[4] = 0x0E;
    send(fd.fd, buf2, 16, 0);
    sp_packet pack2(fd, 8, 10, 8);
    auto d = pack2.serialize();
    send(fd.fd, d.data(), d.size(), 0);
    server_pl_packet pack = server_pl_packet(fd, 5.0, 1.5, 10.0, 5.0, 0, 0, 1);
    auto data = pack.serialize();
    send(fd.fd, data.data(), data.size(), 0);
    uint8_t buf3[13] = {0};
    buf3[0] = 0x06;
    send(fd.fd, buf3, 13, 0);
}

}

