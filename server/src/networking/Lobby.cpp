/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Lobby
*/

#include <asio.hpp>
#include "networking/Lobby.hpp"
#include "networking/tcp/Connection.hpp"

namespace rtype {
  namespace net {

    Lobby::Lobby(int port, bool debug, asio::io_context& io_context)
    : io_context_(io_context),
      acceptor_(io_context, tcp::endpoint(tcp::v4(), port)),
      _debug(debug)
  {
    start_accept();
  }

  void Lobby::start_accept()
  {
    Connection::pointer new_connection =
      Connection::create(io_context_);

    acceptor_.async_accept(new_connection->socket(),
        std::bind(&Lobby::handle_accept, this, new_connection,
          asio::placeholders::error));
  }

  void Lobby::handle_accept(Connection::pointer new_connection,
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

  }  // namespace net
}  // namespace rtype
