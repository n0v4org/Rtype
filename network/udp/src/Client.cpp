/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Client
*/

#include <string>
#include <iostream>
#include <asio.hpp>
#include "Input.hpp"
#include "Commands.hpp"
#include "Client.hpp"

using asio::ip::udp;

namespace network {
  namespace game {

    Client::Client(int server_port, int client_port, std::string ip,
                   asio::io_context &service)
      : _socket(service, udp::endpoint(udp::v4(), client_port))
      , _io_service(service)
      , _sequence_id(0) {
      udp::resolver resolver(_io_service);
      udp::resolver::query query(udp::v4(), ip, std::to_string(server_port));
      udp::resolver::iterator iter = resolver.resolve(query);
      _server_endpoint             = *iter;
      std::cout << "Connecting to: " << _server_endpoint.address().to_string()
                << ":" << _server_endpoint.port() << " " << ip << std::endl;

      startReceive();
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

    void Client::close_connection() {
      if (_socket.is_open()) {
        _socket.cancel();
        _socket.close();
      }
    }

    void Client::startReceive() {
      _socket.async_receive_from(
          asio::buffer(_recvBuffer), _remote_endpoint,
          [this](const asio::error_code &error, std::size_t bytes_transferred) {
            handleReceive(error, bytes_transferred);
          });
    }

    void Client::handleReceive(const asio::error_code &error,
                               std::size_t bytes_transferred) {
      if (!error && bytes_transferred > 0) {
        input_t receivedMessage = unpack(bytes_transferred, _recvBuffer);

        {
            std::lock_guard<std::mutex> lock(_mutex);

            auto& client_set = _read_id[receivedMessage.id];

            if (client_set.find(receivedMessage.seq) == client_set.end()) {
                _command_queue.push_back(receivedMessage);
                client_set.insert(receivedMessage.seq);
            }
        }
        startReceive();
      } else if (error) {
        std::cerr << "Receive error: " << error.message() << std::endl;
      }
    }

    Client::~Client() {
      close_connection();
    }

  }  // namespace game
}  // namespace network