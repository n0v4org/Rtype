/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** utils
*/

#include <vector>
#include <cmath>
#include <sstream>
#include <iostream>
#include <random>
#include <string>

#include "Lobby.hpp"

namespace rtype {

  std::vector<std::string> Lobby::parse_input(std::string input) {
    std::stringstream ss(input.c_str());
    std::string line;
    std::vector<std::string> cmds;

    while (std::getline(ss, line, SP)) {
      cmds.push_back(line);
    }
    return cmds;
  }

  int Lobby::get_player_lobby(int player_id) {
    for (int i = 0; i < _lobby.size(); i++) {
      std::vector<player_t>::iterator it =
          std::find_if(_lobby.at(i).players.begin(), _lobby.at(i).players.end(),
                       [player_id](const player_t &player) {
                         return player_id == player.id;
                       });
      if (it != _lobby.at(i).players.end())
        return i;
    }
    return -1;
  }

  std::string Lobby::generateFixedLengthString() {
    size_t length = 20;

    const size_t charsetSize = sizeof(CHARSET) - 1;

    std::string result;
    result.reserve(length);

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, charsetSize - 1);

    for (size_t i = 0; i < length; ++i) {
      result += CHARSET[distribution(generator)];
    }

    return result;
  }

  int Lobby::get_lobby_id(input_t input) {
    auto it =
        std::find_if(_lobby.begin(), _lobby.end(), [input](const room_t &room) {
          auto player_it =
              std::find_if(room.players.begin(), room.players.end(),
                           [input](const player_t &player) {
                             return player.id == input.id;
                           });
          return player_it != room.players.end();
        });
    if (it == _lobby.end()) {
      send_error(input.id, TCP_ERRORS.at(NOT_IN_ROOM).second,
                 TCP_ERRORS.at(NOT_IN_ROOM).first);
      return 84;
    }
    return it - _lobby.begin();
  }

  bool Lobby::check_start_game(int room, input_t input) {
    if (room == 84)
        return false;
      if (bad_room(input, room))
        return false;
      player_t temp_player = {};
      bool status          = false;
      for (const auto& room : _lobby) {
        for (const auto& player : room.players) {
          if (player.id == input.id) {
            status      = true;
            temp_player = player;
          }
        }
      }
      if (!status) {
        send_error(input.id, TCP_ERRORS.at(NOT_IN_ROOM).second,
                           TCP_ERRORS.at(NOT_IN_ROOM).first);
        return false;
      }
      if (!temp_player.is_admin &&
          _lobby.at(room).owner != DEFAULT_OWNER) {
        send_error(input.id, TCP_ERRORS.at(NOT_ADMIN).second,
                           TCP_ERRORS.at(NOT_ADMIN).first);
        return false;
      }
      for (const auto& player : _lobby.at(room).players) {
        if (!player.is_ready) {
          send_error(input.id, TCP_ERRORS.at(NOT_READY).second,
                             TCP_ERRORS.at(NOT_READY).first);
          return false;
        }
      }
      if (_lobby.at(room).running) {
        send_error(input.id, TCP_ERRORS.at(GAME_ALREADY_RUNNING).second,
                           TCP_ERRORS.at(GAME_ALREADY_RUNNING).first);
        return false;
      }
      return true;
  }

}  // namespace rtype