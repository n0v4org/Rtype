/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** get
*/

#include <vector>
#include <cmath>
#include <sstream>
#include <iostream>
#include <random>
#include <string>

#include "macro.hpp"
#include "Lobby.hpp"

namespace rtype {
  void Lobby::LobbyGetCmd() {
    // Command to retrieve info on all lobby
    _engine.registerCommandTcp(GET_ALL_LOBBY_CMD, [this](zef::Engine& engine,
                                                         input_t input) {
      std::string res = CMD_RES.at(GET_ALL_LOBBY_CMD).at(SUCCESS);

      if (bad_args(input, std::stoi(CMD_RES.at(GET_ALL_LOBBY_CMD).at(NB_ARGS))))
        return;
      json data;
      data["rooms"] = json::array();
      for (int i = 0; i < _lobby.size(); i++) {
        json room_data = get_data_single_room(_lobby.at(i), i);
        data["rooms"].push_back(room_data);
      }
      data["status"]      = std::stoi(CMD_RES.at(GET_ALL_LOBBY_CMD).at(STATUS));
      data["description"] = res;
      _engine.ServerSendTcp(input.id, data.dump());
    });

    // Command to retrieve info on a target room
    _engine.registerCommandTcp(GET_LOBBY_CMD, [this](zef::Engine& engine,
                                                     input_t input) {
      std::string res = CMD_RES.at(GET_LOBBY_CMD).at(SUCCESS);

      if (bad_args(input, std::stoi(CMD_RES.at(GET_LOBBY_CMD).at(NB_ARGS))) ||
          !is_number(input.tcp_payload, input.id))
        return;
      int room = std::stoi(input.tcp_payload);
      if (bad_room(input, room))
        return;
      res += std::to_string(room);
      json data           = get_data_single_room(_lobby.at(room), room);
      data["status"]      = std::stoi(CMD_RES.at(GET_LOBBY_CMD).at(STATUS));
      data["description"] = res;
      _engine.ServerSendTcp(input.id, data.dump());
    });

    _engine.registerCommandTcp(GET_LOBBY_ID_CMD, [this](zef::Engine& engine, input_t input) {
      std::string res = CMD_RES.at(GET_LOBBY_ID_CMD).at(SUCCESS);

      if (bad_args(input, std::stoi(CMD_RES.at(GET_LOBBY_ID_CMD).at(NB_ARGS))))
        return;
      int lobby_id = get_lobby_id(input);
      if (lobby_id == KO)
        return;
      json data;
      data["status"]      = std::stoi(CMD_RES.at(GET_LOBBY_ID_CMD).at(STATUS));
      data["description"] = res;
      data["room_id"] = lobby_id;
      _engine.ServerSendTcp(input.id, data.dump());
    });

    _engine.registerCommandTcp(GET_PLAYER_DATA_CMD, [this](zef::Engine& engine, input_t input) {
      std::string res = CMD_RES.at(GET_PLAYER_DATA_CMD).at(SUCCESS);

      if (bad_args(input, std::stoi(CMD_RES.at(GET_PLAYER_DATA_CMD).at(NB_ARGS))))
        return;
      int lobby_id = get_lobby_id(input);
      if (lobby_id == KO)
        return;
      std::vector<player_t>::iterator it = std::find_if(
          _lobby.at(lobby_id).players.begin(), _lobby.at(lobby_id).players.end(),
          [input](const player_t& player) { return input.id == player.id; });
      if (it == _lobby.at(lobby_id).players.end()) {
        send_error(input.id, TCP_ERRORS.at(NOT_IN_ROOM).second,
                   TCP_ERRORS.at(NOT_IN_ROOM).first);
        return;
      }
      json data;
      data["status"]      = std::stoi(CMD_RES.at(GET_PLAYER_DATA_CMD).at(STATUS));
      data["description"] = res;
      data["room_id"] = lobby_id;
      data["id"] = input.id;
      data["is_admin"] = (*it).is_admin;
      data["is_ready"] = (*it).is_ready;
      _engine.ServerSendTcp(input.id, data.dump());
    });
  }

}  // namespace rtype