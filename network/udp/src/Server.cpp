/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Server
*/

#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <asio.hpp>
#include "Server.hpp"
#include "Commands.hpp"

namespace network {
  namespace game {

    Server::Server(asio::io_context& context, int port)
      : _socket(context, udp::endpoint(udp::v4(), port)), _sequence_id(0) {
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

    bool Server::is_registered() {
      for (auto& i : _clients) {
        if (i == _remote_endpoint_) {
          return true;
        }
      }
      return false;
    }

    void Server::dispatch_client(const std::error_code& ec,
                                 std::size_t bytes_transferred) {
      if (ec) {
        std::cerr << "Error during receive: " << ec.message() << std::endl;
        start_receive();
        return;
      }

      try {
        if (std::find(_clients.begin(), _clients.end(), _remote_endpoint_) ==
            _clients.end()) {
          _clients.push_back(_remote_endpoint_);
        }
        auto f = std::find(_clients.begin(), _clients.end(), _remote_endpoint_);
        if (f == _clients.end())
          throw std::runtime_error("client does not exist");
        input_t message = unpack(bytes_transferred, _recv_buffer_);
        auto it    = find(_clients.begin(), _clients.end(), _remote_endpoint_);
        message.id = it - _clients.begin();
        {
           std::lock_guard<std::mutex> lock(_mutex);

            auto& client_set = _read_id[message.id];

            if (client_set.find(message.seq) == client_set.end()) {
                _command_queue.push_back(message);
                client_set.insert(message.seq);
            }
        }

      } catch (const std::exception& e) {
        std::cerr << "Error handling client message: " << e.what() << std::endl;
      }

      start_receive();
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

    std::vector<int> Server::getAllIds() {
      std::vector<int> ret;
      int t = 0;
      for (auto& i : _clients) {
        ret.push_back(t);
        t++;
      }
      return ret;
    }

  }  // namespace game
}  // namespace network