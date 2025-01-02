/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Network_client
*/

#include <iostream>
#include <memory>
#include <string>
#include <asio.hpp>

#include "Client.hpp"
#include "Network_client.hpp"

namespace network {

Network_client::Network_client(int server_port, int client_port, std::string ip)
{
    _client_udp = std::make_shared<game::Client>(server_port, client_port, ip, _io_service);
}

std::shared_ptr<game::Client> Network_client::get_udp_client() const {
    return _client_udp;
}

Network_client::~Network_client()
{
}

}  // namespace Network_server
