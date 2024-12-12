/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Tcp
*/

#ifndef SERVER_INCLUDE_NETWORKING_TCP_CONNECTION_HPP_
#define SERVER_INCLUDE_NETWORKING_TCP_CONNECTION_HPP_

#include <string>
#include <memory>
#include <iostream>
#include <asio.hpp>

using asio::ip::tcp;


namespace network {
    namespace lobby {
        class Connection
  : public std::enable_shared_from_this<Connection>
{
public:
  typedef std::shared_ptr<Connection> pointer;

  static pointer create(asio::io_context& io_context)
  {
    return pointer(new Connection(io_context));
  }

  tcp::socket& socket()
  {
    return socket_;
  }

  void write(std::string msg)
  {
    asio::async_write(socket_, asio::buffer("test"),
        std::bind(&Connection::handle_write, shared_from_this(),
          asio::placeholders::error,
          asio::placeholders::bytes_transferred));
  }

  void start()
  {
    write("200");
  }

private:
  explicit Connection(asio::io_context& io_context)
    : socket_(io_context)
  {
  }

  void read() {
    socket_.async_read_some(asio::buffer(_data, 1024),
        std::bind(&Connection::handle_read, shared_from_this(),
          asio::placeholders::error,
          asio::placeholders::bytes_transferred));
  }

  void handle_write(const std::error_code& /*error*/,
      size_t bytes_transferred)
  {
    read();
  }

  void handle_read(const std::error_code& /*error*/,
      size_t bytes_transferred)
  {
    std::cout << std::string(_data, bytes_transferred) << std::endl;
    read();
  }
  asio::ip::tcp::socket socket_;
  std::string message_;
  char _data[1024];
};
    }
  }  // namespace net

#endif  // SERVER_INCLUDE_NETWORKING_TCP_CONNECTION_HPP_
