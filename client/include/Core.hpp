/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Core
*/

#ifndef CLIENT_INCLUDE_CORE_HPP_
#define CLIENT_INCLUDE_CORE_HPP_

#include <memory>
#include <asio.hpp>
#include "Arguments.hpp"
#include "Lobby.hpp"
#include "Client.hpp"
#include "networking/TcpClient.hpp"

namespace client {

  class Core {
  public:
    Core(int, char *[]);
    void run();
    ~Core();

  protected:
  private:
    std::unique_ptr<Arguments> _params;
    std::unique_ptr<network::game::Client> _client;
    std::shared_ptr<network::lobby::Client> _tcp_client;
    asio::io_context _io_service;
  };

}  // namespace client

#endif  // CLIENT_INCLUDE_CORE_HPP_
