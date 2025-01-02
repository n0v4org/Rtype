/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Network_server
*/

#include <memory>
#include "Server.hpp"
#include "Network_server.hpp"

namespace network {

Network_server::Network_server(int port)
{
  _server_udp = std::make_shared<game::Server>(_io_service, port);
  t = std::thread([this]() { _io_service.run(); });
}

std::shared_ptr<game::Server> Network_server::get_udp_server() const {
    return _server_udp;
}

Network_server::~Network_server()
{
}

}  // namespace Network_server