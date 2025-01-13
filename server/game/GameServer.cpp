/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** game
*/

#include <vector>
#include <cmath>
#include <sstream>
#include <iostream>
#include <random>
#include <string>
#include <memory>

#include "GameServer.hpp"

namespace rtype {

  GameServer::GameServer(int udp_port, int tcp_port) {
    _engine.initServer(udp_port, tcp_port);
    _lobby = std::make_unique<Lobby>(_engine);
    _game = std::make_unique<Game>(_engine);
    _lobby->RegisterLobbyCmd();
    _game->RegisterGameCmd();
    _engine.addSystem<>(ENGINE_NAME, zef::sys::handle_server);
  }

  void GameServer::run() {
    _engine.run();
  }

  GameServer::~GameServer() {
  }

}  // namespace rtype