#include "user_conn.hpp"
#include <optional>

namespace tangle::net {

user_connection::user_connection(ba::ip::tcp::socket&& sock)
: m_username(std::nullopt), m_sock(std::move(sock)) {}

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
    if(m_sock.is_open()) {
        m_sock.cancel();
        m_sock.close();
    }
}

} // namespace tangle::net