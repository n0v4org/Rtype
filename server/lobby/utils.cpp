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

}  // namespace rtype