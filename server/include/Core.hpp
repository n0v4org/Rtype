/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Core
*/

#ifndef SERVER_INCLUDE_CORE_HPP_
#define SERVER_INCLUDE_CORE_HPP_
#include <memory>
#include <boost/asio.hpp>
#include "Arguments.hpp"
#include "networking/Server.hpp"

namespace rtype {

class Core {
public:
  Core(char *[], int);
  void run();
  ~Core();

protected:
private:
  std::unique_ptr<Arguments> _args;
  std::unique_ptr<net::Server> _server;
  boost::asio::io_service _io_service;
};

}  // namespace rtype

#endif  // SERVER_INCLUDE_CORE_HPP_
