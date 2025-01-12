/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** error_handling
*/

#include <vector>
#include <cmath>
#include <sstream>
#include <iostream>
#include <random>
#include <string>

#include "Lobby.hpp"

namespace rtype {

  bool Lobby::bad_args(input_t input, int nb_args) {
    int nb_cmd =
        std::count(input.tcp_payload.begin(), input.tcp_payload.end(), SP);

    if (nb_cmd == 0) {
      if (input.tcp_payload.empty() && nb_args == 0) {
        return false;
      }
      if (!input.tcp_payload.empty() && nb_args == 1)
        return false;
    }
    if (nb_cmd + 1 != nb_args) {
      _engine.ServerSendTcp(input.id, TCP_ERRORS.at(INVALID_ARGS));
      return true;
    }
    return false;
  }

  bool Lobby::bad_room(input_t input, int room) {
    if (room < 0 || room >= _lobby.size()) {
      _engine.ServerSendTcp(input.id, TCP_ERRORS.at(LOBBY_NOT_FOUND));
      return true;
    }
    return false;
  }

  bool Lobby::bad_perm(input_t input, int room) {
    if (_lobby.at(room).owner == DEFAULT_OWNER) {
      _engine.ServerSendTcp(input.id, TCP_ERRORS.at(NO_PERMS));
      return true;
    }
    std::vector<player_t>::iterator it = std::find_if(
        _lobby.at(room).players.begin(), _lobby.at(room).players.end(),
        [input](const player_t& player) {
          return input.id == player.id && player.is_admin;
        });
    if (it == _lobby.at(room).players.end() &&
        _lobby.at(room).owner != input.id) {
      _engine.ServerSendTcp(input.id, TCP_ERRORS.at(NOT_OWNER));
      return true;
    }
    return false;
  }

  bool Lobby::is_number(const std::string& s, int id) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    if (s.empty() || it != s.end()) {
      _engine.ServerSendTcp(id, TCP_ERRORS.at(NOT_A_NUMBER));
      return false;
    }
    return true;
    ;
  }
}  // namespace rtype