#ifndef TANGLE_NET_NETWORK_H
#define TANGLE_NET_NETWORK_H

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/system/detail/error_code.hpp>
#include <memory>

#include <common/queue.hh>
#include <net/user_conn.hh>
#include <net/packet/incoming_packet.hh>

#define NUM_THREADS 4

namespace ba = boost::asio;

namespace tangle::net {

using namespace common;
using namespace packet;

class network {
    ba::io_context m_ctx_;
    ba::ip::tcp::acceptor m_acceptor;
    std::shared_ptr<buf_fac> m_factory;
    std::unordered_map<ba::ip::tcp::endpoint, std::shared_ptr<user_connection>> m_connections;
public:
    network();
    void bind();
    void accept(queue<std::unique_ptr<incoming_packet>>& queue);
    void accept_task(boost::system::error_code ec, ba::ip::tcp::socket sock, queue<std::unique_ptr<incoming_packet>>& queue);
    void run();
    void stop();
    ~network();        
};

}

#endif // TANGLE_NET_NETWORK_H