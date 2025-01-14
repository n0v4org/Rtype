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

#include "Lobby.hpp"

namespace rtype {
  void Lobby::LobbyActionCmd() {
    // Command to join a room
    _engine.registerCommandTcp(JOIN_ROOM_CMD, [this](zef::Engine& engine,
                                                     input_t input) {
      std::string res = CMD_RES.at(JOIN_ROOM_CMD).at(SUCCESS);

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

      player_t new_player = {0};
      new_player.id       = input.id;
      new_player.is_admin = (_lobby.at(room).owner == input.id) ? true : false;
      new_player.is_ready = false;

      // player_t new_player = {
      //     .id       = input.id,
      //     .is_admin = (_lobby.at(room).owner == input.id) ? true : false,
      //     .is_ready = false,
      // };

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

      if (bad_args(input, std::stoi(CMD_RES.at(QUIT_ROOM_CMD).at(NB_ARGS))) ||
          !is_number(input.tcp_payload, input.id))
        return;
      int room = std::stoi(input.tcp_payload);
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
    });

    // Command to laucnh a Game
    _engine.registerCommandTcp(LAUNCH_GAME_CMD, [this](zef::Engine& engine,
                                                       input_t input) {
      std::string res = CMD_RES.at(LAUNCH_GAME_CMD).at(SUCCESS);

      if (bad_args(input, std::stoi(CMD_RES.at(LAUNCH_GAME_CMD).at(NB_ARGS))) ||
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
      if (!(*it).is_admin && _lobby.at(room).owner != DEFAULT_OWNER) {
        send_error(input.id, TCP_ERRORS.at(NOT_ADMIN).second,
                   TCP_ERRORS.at(NOT_ADMIN).first);
        return;
      }
      it = std::find_if(
          _lobby.at(room).players.begin(), _lobby.at(room).players.end(),
          [](const player_t& player) { return !player.is_ready; });
      if (it != _lobby.at(room).players.end()) {
        send_error(input.id, TCP_ERRORS.at(NOT_READY).second,
                   TCP_ERRORS.at(NOT_READY).first);
        return;
      }
      // add logic to launch a game in intern
      _lobby.at(room).running = true;
      res += _lobby.at(room).name;
      json data;
      data["status"]      = std::stoi(CMD_RES.at(QUIT_ROOM_CMD).at(STATUS));
      data["description"] = res;
      data["room_id"]     = room;
      for (auto player : _lobby.at(room).players) {
        _engine.ServerSendTcp(input.id, data.dump());
      }
    });

    // Command to kick a player
    _engine.registerCommandTcp(KICK_PLAYER_CMD, [this](zef::Engine& engine,
                                                       input_t input) {
      std::string res = CMD_RES.at(KICK_PLAYER_CMD).at(SUCCESS);
      if (bad_args(input, std::stoi(CMD_RES.at(KICK_PLAYER_CMD).at(NB_ARGS))))
        return;
      std::vector<std::string> parsed_input = parse_input(input.tcp_payload);
      if (!is_number(parsed_input.at(0), input.id) ||
          !is_number(parsed_input.at(1), input.id))
        return;
      int room      = std::stoi(parsed_input.at(0));
      int player_id = std::stoi(parsed_input.at(1));
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
  }

}  // namespace rtype