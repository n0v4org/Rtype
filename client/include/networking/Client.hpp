/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Client
*/

#ifndef CLIENT_INCLUDE_NETWORKING_CLIENT_HPP_
#define CLIENT_INCLUDE_NETWORKING_CLIENT_HPP_
#include <string>
#include <array>
#include <thread>
#include <asio.hpp>
#include "macro.hpp"

using asio::ip::udp;

namespace client {
  namespace net {

    class Client {
    public:
      Client(int, int, std::string, asio::io_context &);
      void recv_thread();
      void close_connection();
      void send(const std::string &, uint8_t);
      void startReceive();
      ~Client();

    protected:
    private:
      uint32_t _sequence_id;
      udp::socket _socket;
      asio::io_context &_io_service;
      udp::endpoint _server_endpoint;
      udp::endpoint _remote_endpoint;
      std::array<char, BUFFER_SIZE> _recvBuffer;
      std::thread _recv_thread;
    };

  }  // namespace net
}  // namespace client

#endif  // CLIENT_INCLUDE_NETWORKING_CLIENT_HPP_
