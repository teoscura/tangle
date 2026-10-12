#include <cstddef>
#include <net/user_conn.hh>

#include <boost/asio/buffer.hpp>
#include <boost/system/detail/error_code.hpp>
#include <memory>
#include <optional>
#include <print>

#include <common/bytestream.hh>
#include <net/packet/deserializer.hh>
#include <net/packet/incoming_packet.hh>

namespace tangle::net {

using ec = boost::system::error_code;

user_connection::user_connection(std::shared_ptr<buf_fac> factory, ba::ip::tcp::socket&& sock)
: m_factory(factory)
, m_username(std::nullopt)
, m_sock(std::move(sock)) 
, m_cd(m_sock.native_handle()) {}

void user_connection::start(queue<std::unique_ptr<incoming_packet>>& queue) {
    read(queue);
}

void user_connection::read(queue<std::unique_ptr<incoming_packet>>& queue) {
    auto buf = m_factory->get_or();
    buf->resize(0x1000);
    ba::mutable_buffer mutbuf(buf->data(), buf->size());
    m_sock.async_read_some(mutbuf, [this, buf = std::move(buf), &queue](boost::system::error_code ec, std::size_t recv) mutable {
        std::println("read1");
        if(ec) {
            return;
        }
        read_task(queue, std::move(buf), recv);
        std::println("read2");
        read(queue);
    });
}

void user_connection::read_task(queue<std::unique_ptr<incoming_packet>>& queue, buf_fac::value buffer, std::size_t recv) {
    if(recv == 0) {
        std::println("Connection closed!");
        stop();
        return;
    }
    deserializer des;
    bebyteistream str(buffer->data(), recv);
    queue.push(des.deserialize(m_cd, str));
    return;
}

void user_connection::send(buf_fac::value&& buffer, std::size_t size) {
    assert(size <= buffer->size());
    ba::const_buffer buf(buffer->data(), size);
    m_sock.async_send(buf, [this, buffer = std::move(buffer)](ec e, std::size_t sent) mutable {
        if(e) {
            m_sock.close();
            return;
        }
        if(sent < buffer->size()) {
            m_sock.close();
            return;
        }
    });
}

void user_connection::stop() {
    if(m_sock.is_open()) {
        m_sock.cancel();
        m_sock.close();
    }
}

bool user_connection::register_name(std::string name) {
    if(m_username.has_value()) return false;
    m_username = name;
    return true;
}

ba::ip::tcp::socket& user_connection::sock() {
    return m_sock;
}

bool user_connection::is_registered() const {
    return m_username.has_value();
}

std::string user_connection::username() const {
    return m_username.has_value() ? *m_username : "";
}

user_connection::~user_connection() {
    stop();
}

} // namespace tangle::net