/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Lobby
*/

#ifndef SERVER_INCLUDE_NETWORKING_LOBBY_HPP_
#define SERVER_INCLUDE_NETWORKING_LOBBY_HPP_
#include <asio.hpp>
#include <vector>
#include <array>
#include <iostream>
#include "Connection.hpp"
#include "Commands/FactoryCmd.hpp"
#include "Commands/ACommand.hpp"

extern std::array<std::vector<asio::ip::tcp::endpoint>, 5> LOBBY;

using asio::ip::tcp;

  namespace network {
    namespace lobby {

class Server {
    public:
  Server(int, bool, asio::io_context&);

private:
  void start_accept();
  void handle_accept(Connection::pointer,
      const std::error_code&);

  asio::io_context& io_context_;
  tcp::acceptor acceptor_;
  bool _debug;
};
    }
  }  // namespace net


#endif  // SERVER_INCLUDE_NETWORKING_LOBBY_HPP_