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
#include <vector>
#include <asio.hpp>
#include "Connection.hpp"
#include "queue.hpp"
#include "Input.hpp"

using asio::ip::tcp;

namespace network {
  namespace tcp_link {

    class Server {
    public:
      input_t popMessage();
      bool isQueueEmpty();
      Server(asio::io_context&, int);
      void send(int idx, std::string cmd);
      void send_all(const std::string &cmd);

    private:
      void start_accept();
      void handle_accept(Connection::pointer new_connection,
                         const std::error_code& error);
      asio::io_context& io_context_;
      tcp::acceptor acceptor_;
      std::vector<Connection::pointer> _clients;
    };
  }  // namespace tcp_link
}  // namespace network

#endif /* !SERVER_HPP_ */
