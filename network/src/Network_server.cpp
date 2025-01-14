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

  Network_server::Network_server(int lobby_port) {
    _lobby = std::make_shared<tcp_link::Server>(_io_service, lobby_port);
    t           = std::thread([this]() { _io_service.run(); });
  }

  int Network_server::set_new_game(int udp_port, int tcp_port) {
    std::cout << "Setting new game " << std::endl;
    std::cout << udp_port << " " << tcp_port << std::endl;
    std::shared_ptr<game::Server> temp = std::make_shared<game::Server>(_io_service, udp_port);
        std::cout << "create ptr " << std::endl;
    _servers_udp.push_back(temp);
    std::cout << "Setting new game  2" << std::endl;
    _servers_tcp.push_back(std::make_shared<tcp_link::Server>(_io_service, tcp_port));
     std::cout << "Setting new game 3" << std::endl;
    return _servers_tcp.size() - 1;
  }  

  std::shared_ptr<game::Server> Network_server::get_udp_server(int idx) const {
    if (idx >= _servers_udp.size()) {
      return nullptr;
    }
    return _servers_udp.at(idx);
  }

  std::shared_ptr<tcp_link::Server> Network_server::get_tcp_server(int idx) const {
    if (idx >= _servers_tcp.size()) {
      return nullptr;
    }
    return _servers_tcp.at(idx);
  }

  std::shared_ptr<tcp_link::Server> Network_server::get_lobby() const {
    return _lobby;
  }

  input_t Network_server::popMessage(int idx) {
    if (DEFAULT_LOBBY_ID == idx) {
      if (!_lobby->isQueueEmpty()) {
        return _lobby->popMessage();
      }
      return {};
    }
    if (!_servers_udp.at(idx)->isQueueEmpty()) {
      return _servers_udp.at(idx)->popMessage();
    }
    if (!_servers_tcp.at(idx)->isQueueEmpty()) {
      return _servers_tcp.at(idx)->popMessage();
    }
    return {};
  }

  bool Network_server::isQueueEmpty(int idx) {
    if (idx == DEFAULT_LOBBY_ID) {
      return _lobby->isQueueEmpty();
    }
    return _servers_udp.at(idx)->isQueueEmpty() && _servers_tcp.at(idx)->isQueueEmpty();
  }

  Network_server::~Network_server() {
  }

}  // namespace network