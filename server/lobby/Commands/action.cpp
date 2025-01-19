/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** action
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
  void Lobby::LobbyActionCmd() {
    // Command to join a room
    _engine.registerCommandTcp(JOIN_ROOM_CMD, [this](zef::Engine& engine,
                                                     input_t input) {
      std::string res = CMD_RES.at(JOIN_ROOM_CMD).at(SUCCESS);
      std::cout << '|' << input.tcp_payload << '|' << std::endl;

      if (bad_args(input, std::stoi(CMD_RES.at(JOIN_ROOM_CMD).at(NB_ARGS))))
        return;

      std::vector<std::string> parsed_input = parse_input(input.tcp_payload);
      if (!is_number(parsed_input.at(0), input.id))
        return;
      int room        = std::stoi(parsed_input.at(0));
      std::string pwd = parsed_input.at(1);

      if (bad_room(input, room))
        return;
      if (_lobby.at(room).pwd != pwd) {
        send_error(input.id, TCP_ERRORS.at(INVALID_PWD).second,
                   TCP_ERRORS.at(INVALID_PWD).first);
        return;
      }
      if (_lobby.at(room).players.size() >= LOBBY_SIZE) {
        send_error(input.id, TCP_ERRORS.at(FULL_ROOM).second,
                   TCP_ERRORS.at(FULL_ROOM).first);
        return;
      }
      for (auto player : _lobby.at(room).players) {
        if (player.id == input.id) {
          send_error(input.id, TCP_ERRORS.at(ALREADY_IN_ROOM).second,
                     TCP_ERRORS.at(ALREADY_IN_ROOM).first);
          return;
        }
      }

      player_t new_player = {};
      new_player.id       = input.id;
      new_player.is_admin = (_lobby.at(room).owner == input.id) ? true : false;
      new_player.is_ready = false;

      if (_usernames.find(input.id) == _usernames.end()) {
        _usernames[input.id] =
            PLAYER + std::to_string(_lobby.at(room).players.size());
      }
      _lobby.at(room).players.push_back(new_player);
      res += std::to_string(room);
      json data           = get_data_single_room(_lobby.at(room), room);
      data["status"]      = std::stoi(CMD_RES.at(JOIN_ROOM_CMD).at(STATUS));
      data["description"] = res;
      for (auto& player : _lobby.at(room).players)
        _engine.ServerSendTcp(player.id, data.dump());
    });

    // Command to quit a room
    _engine.registerCommandTcp(QUIT_ROOM_CMD, [this](zef::Engine& engine,
                                                     input_t input) {
      std::string res = CMD_RES.at(QUIT_ROOM_CMD).at(SUCCESS);

      if (bad_args(input, std::stoi(CMD_RES.at(QUIT_ROOM_CMD).at(NB_ARGS))))
        return;
      int room = get_lobby_id(input);
      if (room == KO)
        return;
      if (bad_room(input, room))
        return;
      std::vector<player_t>::iterator it = std::find_if(
          _lobby.at(room).players.begin(), _lobby.at(room).players.end(),
          [input](const player_t& player) { return input.id == player.id; });
      if (it == _lobby.at(room).players.end()) {
        send_error(input.id, TCP_ERRORS.at(NOT_IN_ROOM).second,
                   TCP_ERRORS.at(NOT_IN_ROOM).first);
        return;
      }
      _lobby.at(room).players.erase(it);
      res += std::to_string(room);
      json data           = get_data_single_room(_lobby.at(room), room);
      data["status"]      = std::stoi(CMD_RES.at(QUIT_ROOM_CMD).at(STATUS));
      data["description"] = res;
      for (auto& player : _lobby.at(room).players)
        _engine.ServerSendTcp(player.id, data.dump());
      _engine.ServerSendTcp(input.id, data.dump());
    });

    // Command to kick a player
    _engine.registerCommandTcp(KICK_PLAYER_CMD, [this](zef::Engine& engine,
                                                       input_t input) {
      std::string res = CMD_RES.at(KICK_PLAYER_CMD).at(SUCCESS);
      if (bad_args(input, std::stoi(CMD_RES.at(KICK_PLAYER_CMD).at(NB_ARGS))))
        return;
      if (!is_number(input.tcp_payload, input.id))
        return;
      int room = get_lobby_id(input);
      if (room == KO)
        return;
      int player_id = std::stoi(input.tcp_payload);
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
      _lobby.at(room).players.erase(it);
      res += std::to_string(player_id);
      json data;
      data["status"]        = std::stoi(CMD_RES.at(KICK_PLAYER_CMD).at(STATUS));
      data["description"]   = res;
      data["kicked_player"] = player_id;
      data["room_id"]       = room;
      for (auto& player : _lobby.at(room).players)
        _engine.ServerSendTcp(player.id, data.dump());
    });

    // Command to send a message
    _engine.registerCommandTcp(SEND_MSG_CMD, [this](zef::Engine& engine,
                                                    input_t input) {
      std::string res = CMD_RES.at(SEND_MSG_CMD).at(SUCCESS);
      int room        = get_lobby_id(input);
      if (room == KO)
        return;
      std::string msg = input.tcp_payload;
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
      res += std::to_string(room);
      json data;
      data["status"]      = std::stoi(CMD_RES.at(SEND_MSG_CMD).at(STATUS));
      data["description"] = res;
      data["from"]        = _usernames[input.id];
      data["room_id"]     = room;
      data["message"]     = msg;
      for (auto& player : _lobby.at(room).players)
        _engine.ServerSendTcp(player.id, data.dump());
    });
  }

}  // namespace rtype