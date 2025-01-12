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
      _engine.ServerSendTcp(input.id, res);
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
        _engine.ServerSendTcp(input.id, TCP_ERRORS.at(INVALID_SLOT));
        return;
      }
      std::vector<room_t>::iterator it = std::find_if(
          _lobby.begin(), _lobby.end(),
          [&name](const room_t& room) { return room.name == name; });
      if (it != _lobby.end()) {
        _engine.ServerSendTcp(input.id,
                              TCP_ERRORS.at(LOBBY_NAME_ALREADY_EXISTS));
        return;
      }

      room_t new_room = {
          .name    = name,
          .players = {},
          .pwd     = pwd,
          .slot    = slot,
          .owner   = input.id,
      };
      _lobby.push_back(new_room);
      res += name;
      _engine.ServerSendTcp(input.id, res);
    });
  }

}  // namespace rtype