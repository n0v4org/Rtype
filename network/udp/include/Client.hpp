/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Client
*/

#ifndef NETWORK_UDP_INCLUDE_CLIENT_HPP_
#define NETWORK_UDP_INCLUDE_CLIENT_HPP_

#include <string>
#include <array>
#include <deque>
#include <thread>
#include <mutex>
#include <iostream>
#include <asio.hpp>
#include "Commands.hpp"
#include "Input.hpp"
#include "IClient.hpp"

using asio::ip::udp;

namespace network {
  namespace game {

    class Client : public IClient {
    public:
      Client(int server_port, int client_port, std::string ip,
             asio::io_context &service);
      void close_connection();
      input_t popMessage();
      bool isQueueEmpty();
      template <typename T>
      void send(T payload, int cmd) {
        try {
         std::array<uint8_t, 1024> message = Commands<T>::toArray(payload, cmd, _sequence_id);

    // Compress the message
    std::vector<uint8_t> compressed_message = compressVector(
        std::vector<uint8_t>(message.begin(), message.end())
    );

    // Prepare the header (4 bytes for original size + compressed data)
    uint32_t compressed_size = compressed_message.size();
    std::cout << "Compressed size: " << compressed_size << std::endl;
    std::vector<uint8_t> header(4 + compressed_size);
    header[0] = static_cast<uint8_t>((compressed_size >> 24) & 0xFF);
    header[1] = static_cast<uint8_t>((compressed_size >> 16) & 0xFF);
    header[2] = static_cast<uint8_t>((compressed_size >> 8) & 0xFF);
    header[3] = static_cast<uint8_t>(compressed_size & 0xFF);

    // Append compressed message to the header
    std::memcpy(header.data() + 4, compressed_message.data(), compressed_size);
            _socket.send_to(asio::buffer(header), _server_endpoint);
          _sequence_id++;
        } catch (const std::exception &e) {
          std::cerr << "Send error: " << e.what() << std::endl;
        }
      }
      void startReceive();
      ~Client();

    private:
      uint32_t _sequence_id;
      udp::socket _socket;
      asio::io_context &_io_service;
      udp::endpoint _server_endpoint;
      udp::endpoint _remote_endpoint;
      std::array<uint8_t, 1024> _recvBuffer;
      std::deque<input_t> _command_queue;
      std::mutex _mutex;

      void handleReceive(const asio::error_code &error,
                         std::size_t bytes_transferred);
    };
  }  // namespace game
}  // namespace network

#endif  // NETWORK_UDP_INCLUDE_CLIENT_HPP_
