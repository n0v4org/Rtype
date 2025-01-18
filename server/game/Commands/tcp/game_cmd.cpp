/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** tcp_game_cmd
*/

#include <string>
#include <vector>
#include <utility>

#include "Game.hpp"
#include "tcp_cmds.hpp"

namespace rtype {
  void Game::register_tcp_game_cmd() {
    _engine.registerCommandTcp(
        LOGIN_CMD, [this](zef::Engine &engine, input_t input) {
          std::string res = CMD_TCP_RES.at(LOGIN_CMD).at(GAME_SUCCESS);
          if (bad_args(input,
                       std::stoi(CMD_TCP_RES.at(LOGIN_CMD).at(GAME_NB_ARGS))))
            return;
          std::string player_uuid = input.tcp_payload;
          std::vector<std::string>::iterator it =
              std::find_if(_player_uuid.begin(), _player_uuid.end(),
                           [player_uuid](const std::string &uuid) {
                             return uuid == player_uuid;
                           });
          if (it == _player_uuid.end()) {
            send_error(input.id, GAME_TCP_ERRORS.at(WRONG_PWD).second,
                       GAME_TCP_ERRORS.at(WRONG_PWD).first);
            return;
          }
          _players_tcp.push_back(std::make_pair(player_uuid, input.id));
          // engine.ServerSendTcp(input.id, res);
          json data;
          data["status"] = std::stoi(CMD_TCP_RES.at(LOGIN_CMD).at(GAME_STATUS));
          data["description"] = res;
          _engine.ServerSendTcp(input.id, data.dump());
          check_game_start(input);
        });
  }
}  // namespace rtype
