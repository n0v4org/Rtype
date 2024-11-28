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
#include <boost/asio.hpp>
#include "macro.hpp"

using boost::asio::ip::udp;

namespace client {
  namespace net {

    class Client {
    public:
      Client(int, int, std::string, boost::asio::io_service &);
      void recv_thread();
      void close_connection();
      void send(const std::string &, uint8_t);
      void startReceive();
      ~Client();

    protected:
    private:
      uint32_t _sequence_id;
      udp::socket _socket;
      boost::asio::io_service &_io_service;
      udp::endpoint _server_endpoint;
      udp::endpoint _remote_endpoint;
      std::array<char, BUFFER_SIZE> _recvBuffer;
      std::thread _recv_thread;
    };

  }  // namespace net
}  // namespace client

#endif  // CLIENT_INCLUDE_NETWORKING_CLIENT_HPP_
