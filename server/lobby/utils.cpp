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

}  // namespace rtype