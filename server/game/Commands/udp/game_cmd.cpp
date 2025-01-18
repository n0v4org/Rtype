/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** game_cmd
*/

#include <string>
#include <vector>
#include <utility>

#include "Game.hpp"

#include "UdpProtoCommands.hpp"

namespace rtype {

  void Game::register_udp_game_cmd() {
    _engine.registerCommand(LOGIN, [this](zef::Engine &engine, input_t input) {
      network::game::Commands<login_t> cmd_handler =
          network::game::Commands<login_t>(input);
      login_t result                        = cmd_handler.getCommand();
      std::vector<std::string>::iterator it = std::find_if(
          _player_uuid.begin(), _player_uuid.end(),
          [result](const std::string &uuid) { return uuid == result.pwd; });
      if (it == _player_uuid.end()) {
        pwd_error_t error = {"bad password"};
        _engine.ServerSendUdp<pwd_error_t>(input.id, PWD_ERRORS, error);
        return;
      }
      _players_udp.push_back(std::make_pair(result.pwd, input.id));
      check_game_start(input);
    });
  }
}  // namespace rtype
