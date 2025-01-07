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

Network_client::Network_client(int server_port, int client_port, int lobby_port, std::string ip)
{
    _client_udp = std::make_shared<game::Client>(server_port, client_port, ip, _io_service);
    _client_tcp = std::make_shared<tcp_link::Client>(ip, lobby_port,  _io_service);
    t = std::thread([this]() { _io_service.run(); });
}

bool Network_client::isQueueEmpty() {
      return _client_tcp->isQueueEmpty() && _client_udp->isQueueEmpty();
}

input_t Network_client::popMessage() {
    if (!_client_tcp->isQueueEmpty()) {
        return _client_tcp->popMessage();
    }
    if (!_client_udp->isQueueEmpty()) {
        return _client_udp->popMessage();
    }
    return {};
}

std::shared_ptr<game::Client> Network_client::get_udp_client() const {
    return _client_udp;
}

std::shared_ptr<tcp_link::Client> Network_client::get_tcp_client() const {
    return _client_tcp;
}

Network_client::~Network_client()
{
}

}  // namespace network
