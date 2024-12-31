/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Network_client
*/

#ifndef NETWORK_CLIENT_HPP_
#define NETWORK_CLIENT_HPP_

#include <memory>
#include <string>
#include <asio.hpp>
#include "IClient.hpp"

namespace network {
  namespace game {


class Network_client {
    public:
        Network_client(int, int, std::string);
        std::shared_ptr<IClient> get_udp_client() const;
        ~Network_client();

    protected:
    private:
        std::shared_ptr<IClient> _client_udp;
      asio::io_context _io_service;
};

  }  // namespace game
}  // namespace Network_server

#endif /* !NETWORK_CLIENT_HPP_ */
