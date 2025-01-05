/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** Server
*/

#include "../include/Server.hpp"

namespace network {
    namespace tcp_link {

Server::Server(asio::io_context& io_context, int port)
    : io_context_(io_context),
      acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
  {
    std::cout << port << std::endl;
    start_accept();
  }


    } // namespace tcp_link
} //namespace network