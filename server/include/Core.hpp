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
  std::unique_ptr<net::Server> _network;
  boost::asio::io_context _io_context;
};

}  // namespace rtype

#endif  // SERVER_INCLUDE_CORE_HPP_
