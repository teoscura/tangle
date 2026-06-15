#ifndef TANGLE_NET_USER_CONN_H
#define  TANGLE_NET_USER_CONN_H

#include <optional>
#include <string>

#include <boost/asio/ip/tcp.hpp>

namespace tangle::net {

namespace ba = boost::asio;

class user_connection {
public:
    user_connection(ba::ip::tcp::socket&& sock);
    bool register_name(std::string name);
    ba::ip::tcp::socket& sock();
    bool is_registered() const;
    std::string username() const;
    ~user_connection();
private:
    std::optional<std::string> m_username;
    ba::ip::tcp::socket m_sock;
};

} //namespace tangle::net;

#endif // TANGLE_NET_USER_CONN_H