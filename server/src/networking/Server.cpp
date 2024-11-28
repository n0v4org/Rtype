/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Server
*/

#include <iostream>
#include <memory>
#include <thread>
#include <string>
#include <boost/asio.hpp>
#include "networking/Client.hpp"
#include "networking/Server.hpp"

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

    void Server::unpack(std::size_t byte_size)
    {
      uint8_t cmd = _recv_buffer_[0];
      uint16_t data = (_recv_buffer_[1] << 8) | _recv_buffer_[2];
      uint32_t seq = 0;
      for (int i = 0; i < 4; i++) {
        seq = (seq << 8) | _recv_buffer_[3 + i];
      }
      std::cout << "Received command: " << (int)cmd << ", data: " << data << ", seq: " << seq
                << std::endl;
    }

    void Server::dispatch_client(const std::error_code ec,
                                 std::size_t byte_size) {
      if (ec) {
        std::cout << ec << std::endl;
        start_receive();
        return;
      }
      if (_clients.find(_remote_endpoint_) == _clients.end()) {
        std::cout << "New client connected" << std::endl;
        Client new_client;

        _clients[_remote_endpoint_] =
            std::thread(new_client, _remote_endpoint_);
      } else {
        std::cout << "Client already connect" << std::endl;
      }
      unpack(byte_size);
      start_receive();
    }

    void Server::handle_send(std::shared_ptr<std::string>,
                             const std::error_code &, std::size_t) {
      start_receive();
    }

    void Server::close_connection()  {
      _socket.close();
    }

    Server::~Server() {
    }
  }  // namespace net
}  // namespace rtype
