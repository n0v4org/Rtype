/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Lobby
*/

#include <iostream>
#include <asio.hpp>
#include "Lobby.hpp"
#include "Connection.hpp"


std::array<std::vector<asio::ip::tcp::endpoint>, 5> LOBBY;

  namespace network {
    namespace lobby {
    Server::Server(int port, bool debug, asio::io_context& io_context)
    : io_context_(io_context),
      acceptor_(io_context, tcp::endpoint(tcp::v4(), port)),
      _debug(debug)
  {
    auto& _factoryCmd = FactoryCmd::getInstance();
    _factoryCmd.registerAllCommand();
    start_accept();
  }

  void Server::start_accept()
  {
    Connection::pointer new_connection =
      Connection::create(io_context_);

    acceptor_.async_accept(new_connection->socket(),
        std::bind(&Server::handle_accept, this, new_connection,
          asio::placeholders::error));
  }

  void Server::handle_accept(Connection::pointer new_connection,
      const std::error_code& error)
  {
    if (!error)
    {
      std::cout << "new connection" << std::endl;
      new_connection->start();
    } else {
        std::cerr << "Accept failed: " << error.message() << std::endl;
    }
    start_accept();
  } 
    } // namespace lobby
  }  // namespace network
