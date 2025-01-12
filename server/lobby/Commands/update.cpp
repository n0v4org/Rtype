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
        send_error(input.id, TCP_ERRORS.at(NOT_IN_ROOM).second,
                   TCP_ERRORS.at(NOT_IN_ROOM).first);
        return;
      }
      (*it).is_ready = true;
      res += std::to_string((*it).id);
      json data;
      data["status"] = std::stoi(CMD_RES.at(SET_PLAYER_READY_CMD).at(STATUS));
      data["description"] = res;
      data["room_id"]     = room;
      data["player_id"]   = (*it).id;
      for (auto &player: _lobby.at(room).players)
        _engine.ServerSendTcp(player.id, data.dump());
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
        send_error(input.id, TCP_ERRORS.at(INVALID_SLOT).second,
                   TCP_ERRORS.at(INVALID_SLOT).first);
        return;
      }
      std::vector<room_t>::iterator it = std::find_if(
          _lobby.begin(), _lobby.end(), [&lobby_name](const room_t& room) {
            return room.name == lobby_name;
          });
      if (it != _lobby.end()) {
        send_error(input.id, TCP_ERRORS.at(LOBBY_NAME_ALREADY_EXISTS).second,
                   TCP_ERRORS.at(LOBBY_NAME_ALREADY_EXISTS).first);
        return;
      }
      _lobby.at(room).name = lobby_name;
      _lobby.at(room).slot = slot;
      _lobby.at(room).pwd  = password;
      res += std::to_string(room);
      json data           = get_data_single_room(_lobby.at(room), room);
      data["status"]      = std::stoi(CMD_RES.at(UPDATE_ROOM_CMD).at(STATUS));
      data["description"] = res;
      _engine.ServerSendTcp(input.id, data.dump());
    });

    // Command to update a player perms
    _engine.registerCommandTcp(UPDATE_PERM_CMD, [this](zef::Engine& engine,
                                                       input_t input) {
      std::string res = CMD_RES.at(UPDATE_PERM_CMD).at(SUCCESS);
      if (bad_args(input, std::stoi(CMD_RES.at(UPDATE_PERM_CMD).at(NB_ARGS))))
        return;
      std::vector<std::string> parsed_input = parse_input(input.tcp_payload);
      if (!is_number(parsed_input.at(0), input.id) ||
          !is_number(parsed_input.at(1), input.id) ||
          !is_number(parsed_input.at(2), input.id))
        return;
      int room      = std::stoi(parsed_input.at(0));
      int player_id = std::stoi(parsed_input.at(1));
      int status    = std::stoi(parsed_input.at(2));
      if (bad_room(input, room) || bad_perm(input, room))
        return;
      std::vector<player_t>::iterator it = std::find_if(
          _lobby.at(room).players.begin(), _lobby.at(room).players.end(),
          [player_id](const player_t& player) {
            return player.id == player_id;
          });
      if (it == _lobby.at(room).players.end()) {
        send_error(input.id, TCP_ERRORS.at(NOT_IN_ROOM).second,
                   TCP_ERRORS.at(NOT_IN_ROOM).first);
        return;
      }
      (*it).is_admin = (status == 0)                          ? true
                       : (player_id != _lobby.at(room).owner) ? false
                                                              : true;
      res += std::to_string(player_id);
      json data;
      data["status"]      = std::stoi(CMD_RES.at(UPDATE_PERM_CMD).at(STATUS));
      data["description"] = res;
      data["room_id"]     = room;
      data["player_id"]   = player_id;
      data["is_admin"]    = (*it).is_admin;
      for (auto &player: _lobby.at(room).players)
        _engine.ServerSendTcp(player.id, data.dump());
    });
  }

}  // namespace rtype