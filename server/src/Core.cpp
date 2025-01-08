/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Core
*/

#include <cstring>
#include <iostream>
#include <thread>
#include <memory>

#include "Network_server.hpp"
#include "Core.hpp"
#include "macro.hpp"
#include "game.hpp"

static const char USAGE[231] = R"(
usage:
        -h: run server in help mode
        -v: run server in verbose mode
        -gp <port>: run game server on specified port (default is 50000)
        -lp <port>: run lobby server on specified port (default is 50002)
)";

struct test {
  int a;
  char b[24];
  int c;
};

namespace rtype {

  Core::Core(char* argv[], int argc) {

  }

  void Core::run() {
    try {
      _args->parse();
      if (_args->get_help()) {
        std::cout << USAGE << std::endl;
        return;
      }

      return;
    }
  }

  Core::~Core() {

  }

}  // namespace rtype
