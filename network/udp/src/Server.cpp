/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Server
*/

#include <iostream>
#include <cstdint>
#include <asio.hpp>
#include "Server.hpp"
#include "Commands.hpp"

namespace network {
  namespace game {

    Server::Server(asio::io_context& context, int port)
      : _socket(context, udp::endpoint(udp::v4(), port)) {
      start_receive();
    }

    void Server::start_receive() {
      _socket.async_receive_from(
          asio::buffer(_recv_buffer_), _remote_endpoint_,
          [this](const std::error_code& ec, std::size_t bytes_transferred) {
            dispatch_client(ec, bytes_transferred);
          });
    }

    bool Server::isQueueEmpty() {
      std::lock_guard<std::mutex> lock(_mutex);
      return _command_queue.empty();
    }

    input_t Server::popMessage() {
      std::lock_guard<std::mutex> lock(_mutex);
      if (_command_queue.empty()) {
        throw std::runtime_error("Queue is empty");
      }
      input_t message = _command_queue.front();
      _command_queue.pop_front();
      return message;
    }

    void Server::dispatch_client(const std::error_code& ec,
                                 std::size_t bytes_transferred) {
      if (ec) {
        std::cerr << "Error during receive: " << ec.message() << std::endl;
        start_receive();
        return;
      }

      try {
        if (std::find(_clients.begin(), _clients.end(), _remote_endpoint_) == _clients.end()) {
          _clients.push_back(_remote_endpoint_);
        }
        auto f = std::find(_clients.begin(), _clients.end(), _remote_endpoint_);
        if (f == _clients.end())
          throw std::runtime_error("client doesnot exist");
        input_t message = unpack(bytes_transferred, _recv_buffer_);

        {
          std::lock_guard<std::mutex> lock(_mutex);
          _command_queue.push_back(message);
        }

      } catch (const std::exception& e) {
        std::cerr << "Error handling client message: " << e.what() << std::endl;
      }

      start_receive();
    }

    void Server::send(int idx,
                      std::array<uint8_t, 1024> message) {
      _socket.async_send_to(
          asio::buffer(message), _clients[idx],
          [this](const std::error_code& ec, std::size_t bytes_transferred) {
            handle_send(ec, bytes_transferred);
          });
      _sequence_id++;
    }

    void Server::handle_send(const std::error_code& ec,
                             std::size_t bytes_transferred) {
      if (ec) {
        std::cerr << "Error during send: " << ec.message() << std::endl;
      }
    }

    void Server::close_connection() {
      _socket.close();
    }


  std::vector<int> Server::getAllIds() const {
    std::vector<int> ids;
    for (size_t i = 0; i < _clients.size(); ++i) {
      ids.push_back(i);
    }
    return ids;
  }

    Server::~Server() {
      close_connection();
    }

  }  // namespace game
}  // namespace network