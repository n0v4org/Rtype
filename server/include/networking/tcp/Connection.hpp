/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Tcp
*/

#ifndef TCP_HPP_
#define TCP_HPP_

#include <string>
#include <asio.hpp>
#include <memory>
#include <iostream>
#include "macro.hpp"

using asio::ip::tcp;


namespace rtype {
namespace net {
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

  void start()
  {
    socket_.async_read_some(asio::buffer(_data, BUFFER_SIZE),
        std::bind(&Connection::handle_write, shared_from_this(),
          asio::placeholders::error,
          asio::placeholders::bytes_transferred));
  }

private:
  Connection(asio::io_context& io_context)
    : socket_(io_context)
  {
  }
  void handle_write(const std::error_code& /*error*/,
      size_t bytes_transferred)
  {
    std::cout << std::string(_data, bytes_transferred) << std::endl;
    start();
  }
  asio::ip::tcp::socket socket_;
  std::string message_;
  char _data[BUFFER_SIZE];
};
  }  // namespace net
}  // namespace rtype

#endif /* !TCP_HPP_ */
