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
        _engine.ServerSendTcp(input.id, TCP_ERRORS.at(INVALID_PWD));
        return;
      }
      if (_lobby.at(room).players.size() >= LOBBY_SIZE) {
        _engine.ServerSendTcp(input.id, TCP_ERRORS.at(FULL_ROOM));
        return;
      }
      for (auto player : _lobby.at(room).players) {
        if (player.id == input.id) {
          _engine.ServerSendTcp(input.id, TCP_ERRORS.at(ALREADY_IN_ROOM));
          return;
        }
      }

      player_t new_player = {
          .id       = input.id,
          .is_admin = (_lobby.at(room).owner == input.id) ? true : false,
          .is_ready = false,
      };

      _lobby.at(room).players.push_back(new_player);
      res += std::to_string(room);
      _engine.ServerSendTcp(input.id, res);
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
        _engine.ServerSendTcp(input.id, TCP_ERRORS.at(NOT_IN_ROOM));
        return;
      }
      _lobby.at(room).players.erase(it);
      res += std::to_string(room);
      _engine.ServerSendTcp(input.id, res);
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
        _engine.ServerSendTcp(input.id, TCP_ERRORS.at(NOT_IN_ROOM));
        return;
      }
      if (!(*it).is_admin && _lobby.at(room).owner != DEFAULT_OWNER) {
        _engine.ServerSendTcp(input.id, TCP_ERRORS.at(NOT_ADMIN));
        return;
      }
      it = std::find_if(
          _lobby.at(room).players.begin(), _lobby.at(room).players.end(),
          [](const player_t& player) { return !player.is_ready; });
      if (it != _lobby.at(room).players.end()) {
        _engine.ServerSendTcp(input.id, TCP_ERRORS.at(NOT_READY));
        return;
      }
      // add logic to launch a game in intern
      res += _lobby.at(room).name;
      for (auto player : _lobby.at(room).players) {
        _engine.ServerSendTcp(player.id, res);
      }
    });

    // Command to kick a player
    _engine.registerCommandTcp(KICK_PLAYER_CMD, [this](zef::Engine& engine, input_t input) {
        std::string res = CMD_RES.at(KICK_PLAYER_CMD).at(SUCCESS);
        if (bad_args(input, std::stoi(CMD_RES.at(KICK_PLAYER_CMD).at(NB_ARGS))))
          return;
        std::vector<std::string> parsed_input = parse_input(input.tcp_payload);
        if (!is_number(parsed_input.at(0), input.id) ||
          !is_number(parsed_input.at(1), input.id))
        return;
        int room = std::stoi(parsed_input.at(0));
        int player_id = std::stoi(parsed_input.at(1));
        if (bad_room(input, room) || bad_perm(input, room))
            return;
        std::vector<player_t>::iterator it = std::find_if(
            _lobby.at(room).players.begin(), _lobby.at(room).players.end(),
            [player_id](const player_t& player) { return player.id == player_id; });
        if (it == _lobby.at(room).players.end()) {
            _engine.ServerSendTcp(input.id, TCP_ERRORS.at(NOT_IN_ROOM));
            return;
        }
        _lobby.at(room).players.erase(it);
        res += std::to_string(player_id);
        _engine.ServerSendTcp(input.id, res);
    });
  }

}  // namespace rtype