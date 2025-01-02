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
#include "Network_client.hpp"
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
    std::unique_ptr<network::Network_client> _client_udp;
    std::shared_ptr<network::lobby::Client> _tcp_client;
  };

}  // namespace client

#endif  // CLIENT_INCLUDE_CORE_HPP_
