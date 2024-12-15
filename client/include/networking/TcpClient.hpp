/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** TcpClient
*/

#ifndef CLIENT_INCLUDE_NETWORKING_TCPCLIENT_HPP_
#define CLIENT_INCLUDE_NETWORKING_TCPCLIENT_HPP_
#include <string>
#include <asio.hpp>
#include "macro.hpp"

using asio::ip::tcp;

namespace client {
  namespace net {
    class TcpClient {
    public:
      TcpClient(int, int, std::string, asio::io_context &);
      void send(const std::string &);
      void close_connection();
      ~TcpClient();

    protected:
    private:
      tcp::socket _socket;
      asio::io_context &_io_service;
      std::array<char, BUFFER_SIZE> _recvBuffer;
    };
  }  // namespace net
}  // namespace client

#endif  // CLIENT_INCLUDE_NETWORKING_TCPCLIENT_HPP_
