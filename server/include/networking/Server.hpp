/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Server
*/

#ifndef SERVER_INCLUDE_NETWORKING_SERVER_HPP_
#define SERVER_INCLUDE_NETWORKING_SERVER_HPP_
#include <boost/asio.hpp>
#include <string>
#include "macro.hpp"

using boost::asio::ip::udp;

namespace rtype {
namespace net {
class Server {
public:
  Server(int, bool, boost::asio::io_service&);
  ~Server();

protected:
private:
    void start_receive();
    void handle_receive(const std::error_code, std::size_t);
    void handle_send(std::shared_ptr<std::string>, const std::error_code&, std::size_t);
  int _port;
  bool _debug;
  udp::socket _socket;
  std::array<char, BUFFER_SIZE> _recv_buffer_;
    udp::endpoint _remote_endpoint_;
};
}  // namespace net
}  // namespace rtype

#endif  // SERVER_INCLUDE_NETWORKING_SERVER_HPP_
