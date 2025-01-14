/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** set
*/

#include <vector>
#include <cmath>
#include <sstream>
#include <iostream>
#include <random>
#include <string>

#include "Lobby.hpp"

namespace rtype {

  void Lobby::LobbySetCmd() {
    // Command to set an username
    _engine.registerCommandTcp(SET_USERNAME_CMD, [this](zef::Engine& engine,
                                                        input_t input) {
      std::string res = CMD_RES.at(SET_USERNAME_CMD).at(SUCCESS);

      if (bad_args(input, std::stoi(CMD_RES.at(SET_USERNAME_CMD).at(NB_ARGS))))
        return;
      _usernames[input.id] = input.tcp_payload;
      res += _usernames[input.id];
      json data;
      data["status"]      = std::stoi(CMD_RES.at(SET_USERNAME_CMD).at(STATUS));
      data["description"] = res;
      data["player"]   = {{"player_id", input.id}, {"name", input.tcp_payload}};
      int target_lobby = get_player_lobby(input.id);
      if (target_lobby == -1) {
        _engine.ServerSendTcp(input.id, data.dump());
        return;
      } else {
        for (auto& player : _lobby.at(target_lobby).players) {
          _engine.ServerSendTcp(player.id, data.dump());
        }
      }
    });

    // Command to set a new room
    _engine.registerCommandTcp(SET_ROOM_CMD, [this](zef::Engine& engine,
                                                    input_t input) {
      std::string res = CMD_RES.at(SET_ROOM_CMD).at(SUCCESS);

      if (bad_args(input, std::stoi(CMD_RES.at(SET_ROOM_CMD).at(NB_ARGS))))
        return;
      std::vector<std::string> parsed_input = parse_input(input.tcp_payload);
      std::string name                      = parsed_input.at(0);
      if (!is_number(parsed_input.at(1), input.id))
        return;
      int slot        = std::stoi(parsed_input.at(1));
      std::string pwd = parsed_input.at(2);
      if (slot < 0 || slot > LOBBY_SIZE) {
        send_error(input.id, TCP_ERRORS.at(INVALID_SLOT).second,
                   TCP_ERRORS.at(INVALID_SLOT).first);
        return;
      }
      std::vector<room_t>::iterator it = std::find_if(
          _lobby.begin(), _lobby.end(),
          [&name](const room_t& room) { return room.name == name; });
      if (it != _lobby.end()) {
        send_error(input.id, TCP_ERRORS.at(LOBBY_NAME_ALREADY_EXISTS).second,
                   TCP_ERRORS.at(LOBBY_NAME_ALREADY_EXISTS).first);
        return;
      }

      room_t new_room = {};
      new_room.name    = name;
      new_room.players = {};
      new_room.pwd     = pwd;
      new_room.slot    = slot;
      new_room.owner   = input.id;
      new_room.running = false;

      // room_t new_room = {
      //     .name    = name,
      //     .players = {},
      //     .pwd     = pwd,
      //     .slot    = slot,
      //     .owner   = input.id,
      //     .running = false,
      // };
      _lobby.push_back(new_room);
      res += name;
      json data =
          get_data_single_room(_lobby.at(_lobby.size() - 1), _lobby.size() - 1);
      data["status"]      = std::stoi(CMD_RES.at(SET_ROOM_CMD).at(STATUS));
      data["description"] = res;
      _engine.ServerSendToAllTcp(data.dump());
    });
  }

}  // namespace rtype