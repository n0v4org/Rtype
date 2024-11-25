/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Client
*/

#include <boost/asio.hpp>
#include "networking/Client.hpp"

namespace client {
  namespace net {

    Client::Client(int server_port, int client_port, std::string ip, boost::asio::io_service &service)
    : _socket(service, udp::endpoint(udp::v4(), client_port)), _io_service(service)
    {

    }

    void Client::run() {
        
    }

    Client::~Client() {
    }

  }  // namespace net
}  // namespace client
