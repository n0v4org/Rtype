/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <asio.hpp>
#include "Connection.hpp"

using asio::ip::tcp;

namespace network {
    namespace tcp_link {

class Server {
public:
  Server(asio::io_context&, int);

private:
  void start_accept()
  {
    Connection::pointer new_connection =
      Connection::create(io_context_);

    acceptor_.async_accept(new_connection->socket(),
        std::bind(&Server::handle_accept, this, new_connection,
          asio::placeholders::error));
  }

  void handle_accept(Connection::pointer new_connection,
      const std::error_code& error)
  {
    if (!error)
    {
      new_connection->start();
    }
    std::cout << "Connection " << std::endl;

    start_accept();
  }

  asio::io_context& io_context_;
  tcp::acceptor acceptor_;
};

    } // namespace tcp_link
} //namespace network

#endif /* !SERVER_HPP_ */
