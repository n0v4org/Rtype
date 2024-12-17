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

#include "../include/Core.hpp"
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
    _args = std::make_unique<Arguments>(argc, argv);
    // _server = std::make_unique<net::Server>(_args->get_game_port(),
    //                                         _args->get_debug(), _io_service);
    // _lobby = std::make_unique<network::lobby::Server>(
    //     _args->get_lobby_port(), _args->get_debug(), _io_service);
  }

  void Core::run() {
    try {
      _args->parse();
      if (_args->get_help()) {
        std::cout << USAGE << std::endl;
        return;
      }
      runServer();
    } catch (const std::exception& e) {
      std::cerr << e.what() << '\n';
      //t.join();
      //_server->close_connection();
      return;
    }
  }

  Core::~Core() {

    //  _server->close_connection();
  }

}  // namespace rtype
