/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Client
*/

#include <string>
#include <boost/asio.hpp>
#include "networking/Client.hpp"

using boost::asio::ip::udp;

namespace client {
  namespace net {

    Client::Client(int server_port, int client_port, std::string ip,
                   boost::asio::io_service &service)
      : _socket(service, udp::endpoint(udp::v4(), 0)), _io_service(service) {
      udp::resolver resolver(_io_service);
      udp::resolver::query query(udp::v4(), ip, std::to_string(server_port));
      udp::resolver::iterator iter = resolver.resolve(query);
      _server_endpoint             = *iter;
    }

    void Client::send(const std::string &msg) {
      _socket.send_to(boost::asio::buffer(msg), _server_endpoint);
    }

    void Client::close_connection() {
      _socket.close();
    }

    void Client::run() {
    }

    Client::~Client() {
    }

  }  // namespace net
}  // namespace client
