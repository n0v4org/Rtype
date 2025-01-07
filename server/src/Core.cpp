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
    _args   = std::make_unique<Arguments>(argc, argv);
    _network = std::make_unique<network::Network_server>(_args->get_game_port(), _args->get_lobby_port());
  }

  void Core::run() {
    try {
      _args->parse();
      if (_args->get_help()) {
        std::cout << USAGE << std::endl;
        return;
      }
      while (1) {
        if (!_network->isQueueEmpty()) {
          input_t data = _network->popMessage();

          if (data.protocol_type == TCP_CMD) {
            std::cout << "cmd : " << data.tcp_cmd << " payload: " << data.tcp_payload << " " << data.id << std::endl;
            _network->get_tcp_server()->send(data.id, "caca");
          } else {
              network::game::Commands<struct test> test =
              network::game::Commands<struct test>(data);
              std::cout << test.getCommand().a << " " << test.getCommand().b << " "
                    << test.getCommand().c << " id is :" << data.id << std::endl;
          }
        }
      }
    } catch (const std::exception& e) {
      std::cerr << e.what() << '\n';
      _network->get_udp_server()->close_connection();
      return;
    }
  }

  Core::~Core() {
    _network->get_udp_server()->close_connection();
  }

}  // namespace rtype
