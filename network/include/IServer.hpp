/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** IServer
*/

#ifndef NETWORK_UDP_INCLUDE_ISERVER_HPP_
#define NETWORK_UDP_INCLUDE_ISERVER_HPP_

#include <array>
#include <asio.hpp>
#include "Input.hpp"

class IServer {
public:
  virtual void close_connection() = 0;
  virtual input_t popMessage()    = 0;
  virtual bool isQueueEmpty()     = 0;
  virtual ~IServer()              = default;

private:
  virtual void start_receive()                                = 0;
  virtual void dispatch_client(const std::error_code& ec,
                               std::size_t bytes_transferred) = 0;
  virtual void handle_send(const std::error_code& ec,
                           std::size_t bytes_transferred)     = 0;
};

#endif  // NETWORK_UDP_INCLUDE_ISERVER_HPP_
