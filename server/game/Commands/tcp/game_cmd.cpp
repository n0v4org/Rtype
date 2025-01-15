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
      if (bad_args(input, std::stoi(CMD_TCP_RES.at(LOGIN_CMD).at(GAME_NB_ARGS))))
        return;
      std::string player_uuid = input.tcp_payload;
      std::vector<std::string>::iterator it = std::find_if(_player_uuid.begin(), _player_uuid.end(), [player_uuid](const std::string &uuid){
        return uuid == player_uuid;
      });
      if (it == _player_uuid.end()) {
        send_error(input.id, GAME_TCP_ERRORS.at(WRONG_PWD).second, GAME_TCP_ERRORS.at(WRONG_PWD).first);
        return;
      }
      _players_tcp.push_back(input.id);
      engine.ServerSendTcp(input.id, res);
      json data;
      data["status"] = CMD_TCP_RES.at(LOGIN_CMD).at(GAME_STATUS);
      data["description"] = res;
      _engine.ServerSendTcp(input.id, data.dump());
      if (_players_tcp.size() == _player_uuid.size() && _players_udp.size() == _player_uuid.size()) {
        json start_json;
        start_json["status"] = CMD_TCP_RES.at(START_GAME_CMD).at(GAME_STATUS);
        start_json["description"] = CMD_TCP_RES.at(START_GAME_CMD).at(GAME_SUCCESS);
        _engine.ServerSendToAllTcp(start_json.dump());
      }
    });
  }
}  // namespace rtype
