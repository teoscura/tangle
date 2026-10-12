#include "net/packet/incoming_packet.hh"
#include <net/network.hh>

#include <boost/system/detail/error_code.hpp>
#include <print>

#include <common/queue.hh>
#include <net/user_conn.hh>

namespace tangle::net {

static const ba::ip::tcp::endpoint endpoint(ba::ip::make_address_v4("127.0.0.1"), 25561);

network::network()
: m_ctx_(NUM_THREADS)
, m_acceptor(m_ctx_)
, m_factory(std::make_shared<buf_fac>()) {}

void network::bind() {
    if(!m_acceptor.is_open()) {
        m_acceptor.open(endpoint.protocol());
    }

    m_acceptor.bind(endpoint);
    m_acceptor.listen(0x1000);
}

void network::accept(queue<std::unique_ptr<incoming_packet>>& queue) {
    m_acceptor.async_accept([this, &queue](boost::system::error_code ec, ba::ip::tcp::socket sock){
        accept_task(ec, std::move(sock), queue);
        accept(queue);
    });
}

void network::accept_task(boost::system::error_code ec, ba::ip::tcp::socket sock, queue<std::unique_ptr<incoming_packet>>& queue) {
    if(ec) {
        return;
    } else {
        auto ep = sock.remote_endpoint(ec);
        if(ec) {
            std::println("rmep: {}", ec.what());
        }
        auto it = m_connections.find(ep);
        if(it != m_connections.end()) {
            return;
        }
        auto conn = std::make_shared<user_connection>(m_factory, std::move(sock));
        m_connections.insert_or_assign(ep, conn);
        conn->start(queue);
    }
}

void network::run() {
    m_ctx_.run();
}

void network::stop() {
    m_connections.clear();
    if(m_acceptor.is_open()) {
        m_acceptor.cancel();
        m_acceptor.close();
    }
}

network::~network() {
    stop();
}
    
} // namespace tangle::net;