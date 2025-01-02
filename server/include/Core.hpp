/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Core
*/

#ifndef SERVER_INCLUDE_CORE_HPP_
#define SERVER_INCLUDE_CORE_HPP_
#include <memory>
#include <thread>
#include <vector>
#include <asio.hpp>
#include "Network_server.hpp"
#include "Arguments.hpp"
#include "Server.hpp"
#include "Lobby.hpp"

namespace rtype {

  class Core {
  public:
    Core(char *[], int);
    void run();
    ~Core();

  protected:
  private:
    std::unique_ptr<Arguments> _args;
    std::unique_ptr<network::Network_server> _network;
    std::unique_ptr<network::lobby::Server> _lobby;
    asio::io_context _io_service;
    std::vector<std::thread> _games;
    std::thread t;
  };

}  // namespace rtype

#endif  // SERVER_INCLUDE_CORE_HPP_
