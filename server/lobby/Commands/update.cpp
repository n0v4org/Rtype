/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** update
*/

#include <vector>
#include <cmath>
#include <sstream>
#include <iostream>
#include <random>
#include <string>

#include "Lobby.hpp"

namespace rtype {

  void Lobby::lobbyUpdateCmd() {
    // update ready status of a player
    _engine.registerCommandTcp(SET_PLAYER_READY_CMD, [this](zef::Engine& engine,
                                                            input_t input) {
      std::string res = CMD_RES.at(SET_PLAYER_READY_CMD).at(SUCCESS);
      if (bad_args(input, std::stoi(CMD_RES.at(DELETE_ROOM_CMD).at(NB_ARGS))) ||
          !is_number(input.tcp_payload, input.id))
        return;
      int room = std::stoi(input.tcp_payload);
      if (bad_room(input, room))
        return;
      std::vector<player_t>::iterator it = std::find_if(
          _lobby.at(room).players.begin(), _lobby.at(room).players.end(),
          [input](const player_t& player) { return player.id == input.id; });
      if (it == _lobby.at(room).players.end()) {
        _engine.ServerSendTcp(input.id, TCP_ERRORS.at(NOT_IN_ROOM));
        return;
      }
      (*it).is_ready = true;
      res += std::to_string((*it).id);
      _engine.ServerSendTcp(input.id, res);
    });

    // Command to update a room
    _engine.registerCommandTcp(UPDATE_ROOM_CMD, [this](zef::Engine& engine,
                                                       input_t input) {
      std::string res = CMD_RES.at(UPDATE_ROOM_CMD).at(SUCCESS);
      if (bad_args(input, std::stoi(CMD_RES.at(UPDATE_ROOM_CMD).at(NB_ARGS))))
        return;
      std::vector<std::string> parsed_input = parse_input(input.tcp_payload);
      if (!is_number(parsed_input.at(0), input.id) ||
          !is_number(parsed_input.at(2), input.id))
        return;
      int room               = std::stoi(parsed_input.at(0));
      std::string lobby_name = parsed_input.at(1);
      int slot               = std::stoi(parsed_input.at(2));
      std::string password   = parsed_input.at(3);
      if (bad_room(input, room) || bad_perm(input, room))
        return;
      if (slot < 0 || slot > LOBBY_SIZE) {
        _engine.ServerSendTcp(input.id, TCP_ERRORS.at(INVALID_SLOT));
        return;
      }
      std::vector<room_t>::iterator it = std::find_if(
          _lobby.begin(), _lobby.end(), [&lobby_name](const room_t& room) {
            return room.name == lobby_name;
          });
      if (it != _lobby.end()) {
        _engine.ServerSendTcp(input.id,
                              TCP_ERRORS.at(LOBBY_NAME_ALREADY_EXISTS));
        return;
      }
      _lobby.at(room).name = lobby_name;
      _lobby.at(room).slot = slot;
      _lobby.at(room).pwd  = password;
      res += std::to_string(room);
      _engine.ServerSendTcp(input.id, res);
    });

    // Command to update a player perms
  }

}  // namespace rtype