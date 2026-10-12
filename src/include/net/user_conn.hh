#ifndef TANGLE_NET_USER_CONN_H
#define TANGLE_NET_USER_CONN_H

#include <optional>
#include <string>

#include <boost/asio/ip/tcp.hpp>

#include <common/queue.hh>
#include <net/buffer_factory.hh>
#include <net/client_descriptor.hh>
#include <net/packet/incoming_packet.hh>

#define BUF_LEN 0x1000

namespace tangle::net {

namespace ba = boost::asio;

using namespace common;
using namespace packet;

class user_connection  {
    std::shared_ptr<buf_fac> m_factory;
    std::optional<std::string> m_username;
    ba::ip::tcp::socket m_sock;
    client_descriptor m_cd;
public:
    user_connection(std::shared_ptr<buf_fac> factory, ba::ip::tcp::socket&& sock);
    void start(queue<std::unique_ptr<incoming_packet>>& queue);
    void stop();
    void read(queue<std::unique_ptr<incoming_packet>>& queue);
    void read_task(queue<std::unique_ptr<incoming_packet>>& queue, buf_fac::value buffer, std::size_t recv);
    void send(buf_fac::value&& buf, std::size_t size);
    bool register_name(std::string name);
    ba::ip::tcp::socket& sock();
    bool is_registered() const;
    std::string username() const;
    ~user_connection();
};

}

#endif // TANGLE_NET_USER_CONN_H