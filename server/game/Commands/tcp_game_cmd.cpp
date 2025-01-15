/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** tcp_game_cmd
*/

#include "Game.hpp"

namespace rtype {
  void Game::register_tcp_game_cmd() {
    _engine.registerCommandTcp(LOGIN_CMD, [this](zef::Engine& engine, input_t input) {
      std::string res = CMD_TCP_RES.at(LOGIN_CMD).at(GAME_SUCCESS);
    });
  }
}  // namespace rtype
