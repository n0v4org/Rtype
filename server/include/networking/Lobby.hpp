/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Lobby
*/

#ifndef SERVER_INCLUDE_NETWORKING_LOBBY_HPP_
#define SERVER_INCLUDE_NETWORKING_LOBBY_HPP_
#include <iostream>
#include <asio.hpp>
#include "macro.hpp"
#include "tcp/Connection.hpp"

using asio::ip::tcp;

namespace rtype {
  namespace net {

class Lobby {
    public:
  Lobby(int, bool, asio::io_context&);

private:
  void start_accept();
  void handle_accept(Connection::pointer,
      const std::error_code&);

  asio::io_context& io_context_;
  tcp::acceptor acceptor_;
  bool _debug;
};

  }  // namespace net
}  // namespace rtype


#endif  // SERVER_INCLUDE_NETWORKING_LOBBY_HPP_
