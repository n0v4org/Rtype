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

#include "tcp_cmds.hpp"
#include "Game.hpp"

namespace rtype {

  bool Game::bad_args(input_t input, int nb_args) {
    int nb_cmd =
        std::count(input.tcp_payload.begin(), input.tcp_payload.end(), ' ');

    if (nb_cmd == 0) {
      if (input.tcp_payload.empty() && nb_args == 0) {
        return false;
      }
      if (!input.tcp_payload.empty() && nb_args == 1)
        return false;
    }
    if (nb_cmd + 1 != nb_args) {
      send_error(input.id, GAME_TCP_ERRORS.at(WRONG_PWD).second,
                 GAME_TCP_ERRORS.at(WRONG_PWD).first);
      return true;
    }
    return false;
  }
}