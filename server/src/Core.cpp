/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Core
*/

#include <cstring>
#include <iostream>
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
    // _server = std::make_unique<net::Server>(_args->get_game_port(),
    //                                         _args->get_debug(), _io_service);
    _lobby = std::make_unique<network::lobby::Server>(
        _args->get_lobby_port(), _args->get_debug(), _io_service);
  }

  void Core::run() {
    try {
      _args->parse();
      if (_args->get_help()) {
        std::cout << USAGE << std::endl;
        return;
      }
      _io_service.run();
    } catch (const std::exception& e) {
      if (strcmp(e.what(), EXCEPTION) != 0)
        std::cerr << e.what() << '\n';
      throw e;
    }
  }

  Core::~Core() {
    //  _server->close_connection();
  }

}  // namespace rtype
