/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** Client
*/

#include <string>

#include "../include/Client.hpp"

namespace network {
  namespace tcp_link {

    Client::Client(const std::string& host, const int port,
                   asio::io_context& io_service)
      : io_context_(io_service), socket_(io_service) {
      connect(host, port);
    }

    bool Client::isQueueEmpty() {
      std::lock_guard<std::mutex> lock(_mutex);
      return _command_queue.empty();
    }

    input_t Client::popMessage() {
      std::lock_guard<std::mutex> lock(_mutex);
      if (_command_queue.empty()) {
        throw std::runtime_error("Queue is empty");
      }
      input_t message = _command_queue.front();
      _command_queue.pop_front();
      return message;
    }

    Client::~Client() {
      close();
    };
  }  // namespace tcp_link
}  // namespace network
