/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Core
*/

#ifndef CLIENT_INCLUDE_CORE_HPP_
#define CLIENT_INCLUDE_CORE_HPP_
#include <memory>
#include <boost/asio.hpp>
#include "Arguments.hpp"
#include "networking/Client.hpp"

namespace client {

  class Core {
  public:
    Core(int, char *[]);
    void run();
    ~Core();

  protected:
  private:
    std::unique_ptr<Arguments> _params;
    std::unique_ptr<net::Client> _client;
    boost::asio::io_service _io_service;
  };

}  // namespace client

#endif  // CLIENT_INCLUDE_CORE_HPP_
