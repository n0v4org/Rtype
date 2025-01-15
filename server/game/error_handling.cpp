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

#include "Game.hpp"

namespace rtype {

  bool Game::bad_args(input_t input, int nb_args) {
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
      send_error(input.id, TCP_ERRORS.at(INVALID_ARGS).second,
                 TCP_ERRORS.at(INVALID_ARGS).first);
      return true;
    }
    return false;
  }
}