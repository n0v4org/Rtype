/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Client
*/

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0A00
#endif

#ifndef NETWORK_UDP_INCLUDE_CLIENT_HPP_
#define NETWORK_UDP_INCLUDE_CLIENT_HPP_

#include <string>
#include <array>
#include <deque>
#include <thread>
#include <mutex>
#include <asio.hpp>
#include "Input.hpp"

using asio::ip::udp;

namespace network {
  namespace game {

    class Client {
    public:
      Client(int server_port, int client_port, std::string ip,
             asio::io_context &service);
      void close_connection();
      input_t popMessage();
      bool isQueueEmpty();
      void send(std::array<uint8_t, 1024> buff);
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