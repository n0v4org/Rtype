/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** game
*/

#include <string>
#include <iostream>

#include "Game.hpp"

namespace rtype {

  Game::Game() {
    _engine.addSystem<>("zefir", zef::sys::handle_server);
    register_tcp_game_cmd();
  }

  void Game::RegisterGameCmd() {
    
  }

  void Game::launch_game(std::vector<std::string> player_uuid, int tcp_port,
                         int udp_port) {
    
    _engine.initServer(udp_port, tcp_port);
    _engine.run();
  }

  void Game::init_game(std::vector<std::string> player_uuid, int tcp_port,
                       int udp_port) {
    _games.push_back(std::thread([this, player_uuid, tcp_port, udp_port]() {
      this->launch_game(player_uuid, tcp_port, udp_port);
    }));
  }

  Game::~Game() {
  }

}  // namespace rtype
