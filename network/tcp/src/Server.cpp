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
      _clients.push_back(new_connection);
      new_connection->start();
      new_connection->assign_id(_clients.size() - 1);
    }
    start_accept();
  }

  void Server::send(int idx, std::string cmd) {
    _clients.at(idx)->write(cmd);
  }

  bool Server::isQueueEmpty() {
      std::lock_guard<std::mutex> lock(_mutex);
      return tcp_command_queue.empty();
    }

    input_t Server::popMessage() {
      std::lock_guard<std::mutex> lock(_mutex);
      if (tcp_command_queue.empty()) {
        throw std::runtime_error("Queue is empty");
      }
      input_t message = tcp_command_queue.front();
      tcp_command_queue.pop_front();
      return message;
    }


    } // namespace tcp_link
} //namespace network