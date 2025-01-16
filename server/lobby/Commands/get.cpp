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
      auto it = std::find_if(_lobby.begin(), _lobby.end(), [input](const room_t &room){
        auto player_it = std::find_if(room.players.begin(), room.players.end(), [input](const player_t &player) {
          return player.id == input.id;
        });
        return player_it != room.players.end();
      });
      if (it == _lobby.end()) {
        send_error(input.id, TCP_ERRORS.at(NOT_IN_ROOM).second, TCP_ERRORS.at(NOT_IN_ROOM).first);
        return;
      }
      json data;
      data["status"]      = std::stoi(CMD_RES.at(GET_LOBBY_ID_CMD).at(STATUS));
      data["description"] = res;
      data["room_id"] = it - _lobby.begin();
      _engine.ServerSendTcp(input.id, data.dump());
    });
  }
}  // namespace rtype