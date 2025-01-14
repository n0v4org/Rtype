/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** tcp_game_cmd
*/

#include "Game.hpp"

namespace rtype {
  void Game::register_tcp_game_cmd() {
    _engine.registerCommandTcp("tester",
                               [this](zef::Engine& test, input_t input) {
                                 test.ServerSendTcp(input.id, "in game");
                               });
  }
}  // namespace rtype
