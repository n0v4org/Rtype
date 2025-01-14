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

#include "Core.hpp"
#include "macro.hpp"

static const char USAGE[231] = R"(
usage:
        -h: run server in help mode
        -v: run server in verbose mode
        -gp <port>: run game server on specified port (default is 50000)
        -lp <port>: run lobby server on specified port (default is 50002)
)";

namespace rtype {

  Core::Core(char* argv[], int argc) {
    _args = std::make_unique<Arguments>(argc, argv);
  }

  void Core::run() {
    try {
      _args->parse();
      if (_args->get_help()) {
        std::cout << USAGE << std::endl;
        return;
      }
      _server = std::make_unique<GameServer>(_args->get_game_port(),
                                             _args->get_lobby_port());
      _server->run();
    } catch (const std::exception& e) {
      std::cerr << e.what() << '\n';

      return;
    }
  }

  Core::~Core() {
  }

}  // namespace rtype
