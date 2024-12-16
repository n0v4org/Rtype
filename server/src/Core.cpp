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
#include "Commands.hpp"

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
    _server = std::make_unique<network::game::Server>(_io_service, _args->get_game_port());
  }

  void Core::run() {
    try {
      _args->parse();
      if (_args->get_help()) {
        std::cout << USAGE << std::endl;
        return;
      }
      t = std::thread([this]() {
        _io_service.run();
      });
      while (1) {
        if (!_server->isQueueEmpty()) {
          network::game::Commands<struct test> test = network::game::Commands<struct test>(_server->popMessage());
          std::cout << test.getCommand().a << " " << test.getCommand().b << " " << test.getCommand().c << std::endl;
        }
      }
    } catch (const std::exception& e) {
      std::cerr << e.what() << '\n';
      t.join();
      _server->close_connection();
      return;
    }
  }

  Core::~Core() {
      _server->close_connection();
  }

}  // namespace rtype
