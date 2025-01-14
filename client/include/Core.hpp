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
#include "Client.hpp"
#include "Network_client.hpp"

namespace client {

  class Core {
  public:
    Core(int, char *[]);
    void run();
    ~Core();

  protected:
  private:
    std::unique_ptr<Arguments> _params;
    std::unique_ptr<network::Network_client> _network;
  };

}  // namespace client

#endif  // CLIENT_INCLUDE_CORE_HPP_
