/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Client
*/

#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <asio.hpp>
#include "networking/Client.hpp"

using asio::ip::udp;

namespace client {
  namespace net {

    Client::Client(int server_port, int client_port, std::string ip,
                   asio::io_context &service)
      : _socket(service, udp::endpoint(udp::v4(), client_port))
      , _io_service(service)
      , _sequence_id(0) {
      udp::resolver resolver(_io_service);
      udp::resolver::query query(udp::v4(), ip, std::to_string(server_port));
      udp::resolver::iterator iter = resolver.resolve(query);
      _server_endpoint             = *iter;
      _recv_thread                 = std::thread(&Client::recv_thread, this);
    }

    void Client::send(const std::string &msg, uint8_t cmd) {
      std::vector<uint8_t> buff;
      uint16_t payload_size = 5000;
      _sequence_id          = 5689641;

      buff.push_back(cmd);
      buff.push_back((payload_size >> 8) & 0xFF);
      buff.push_back(payload_size & 0xFF);
      for (int i = 3; i >= 0; i--) {
        buff.push_back((_sequence_id >> (8 * i)) & 0xFF);
      }
      _socket.send_to(asio::buffer(buff), _server_endpoint);
      _sequence_id++;
    }

    void Client::close_connection() {
      _socket.close();
    }

    void Client::startReceive() {
      while (1) {
        udp::endpoint remote_endpoint;
        int byteReceived =
            _socket.receive_from(asio::buffer(_recvBuffer), remote_endpoint, 0);
        std::cout << "received : "
                  << std::string(_recvBuffer.data(), byteReceived) << std::endl;
      }
    }

    void Client::recv_thread() {
      try {
        startReceive();
      } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
      }
    }

    Client::~Client() {
    }

  }  // namespace net
}  // namespace client
