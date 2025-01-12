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
      for (int i = 0; i < _lobby.size(); i++) {
        res += _lobby.at(i).name + SP + std::to_string(_lobby.at(i).slot) + SP;
        for (int j = 0; j < _lobby.at(i).players.size(); j++) {
          int id = _lobby.at(i).players.at(j).id;
          res += (_usernames.find(id) == _usernames.end())
                     ? PLAYER + std::to_string(j) + SP
                     : _usernames.at(id);
        }
        res += ";";
      }
      _engine.ServerSendTcp(input.id, res);
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
      res +=
          _lobby.at(room).name + SP + std::to_string(_lobby.at(room).slot) + SP;
      for (int j = 0; j < _lobby.at(room).players.size(); j++) {
        int id = _lobby.at(room).players.at(j).id;
        res += (_usernames.find(id) == _usernames.end())
                   ? PLAYER + std::to_string(j) + SP
                   : _usernames.at(id) + SP;
      }
      _engine.ServerSendTcp(input.id, res);
    });
  }
}  // namespace rtype