/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Server
*/

#include "networking/Client.hpp"
#include "networking/Server.hpp"
#include <iostream>
#include <memory>
#include <thread>
#include <string>
#include <boost/asio.hpp>

namespace rtype {
  namespace net {
    Server::Server(int port, bool debug, boost::asio::io_service &io_service)
      : _port(port)
      , _debug(debug)
      , _socket(io_service, udp::endpoint(udp::v4(), port)) {
      start_receive();
    }

    void Server::start_receive() {
      _socket.async_receive_from(
          boost::asio::buffer(_recv_buffer_), _remote_endpoint_,
          std::bind(&Server::dispatch_client, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
    }

    void Server::dispatch_client(const std::error_code ec,
                                std::size_t byte_size) {
      if (ec) {
        std::cout << ec << std::endl;
        start_receive();
        return;
      }
        if (_clients.find(_remote_endpoint_) == _clients.end()) {
            Client new_client;

            _clients[_remote_endpoint_] = std::thread(new_client, _remote_endpoint_);
        } else {
            std::cout << "Client already connect" << std::endl;
        }
        start_receive();
    }

    void Server::handle_send(std::shared_ptr<std::string>,
                             const std::error_code &, std::size_t) {
      start_receive();
    }

    Server::~Server() {
    }
  }  // namespace net
}  // namespace rtype
