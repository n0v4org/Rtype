/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Core
*/

#include <cstring>
#include <memory>
#include <iostream>
#include <string>
#include <thread>
#include "Arguments.hpp"
#include "Network_client.hpp"
#include "Core.hpp"
#include "Commands.hpp"
#include "macro.hpp"

static const char USAGE[406] = R"(
usage:
        -h: run client in help mode
        -ip <server ip>: run network client with specified server ip
        -sp <port>: specified server port (default is 50000)
        -cp <port>: run newtork client in a specified port (default is 50001)
        -lsp <port>: specified server lobby port (default is 50003)
        -lcp <port>: run newtork client lobby in a specified port (default is 50004)
)";

struct test {
  int a;
  char b[24];
  int c;
};

namespace client {

  Core::Core(int argc, char *argv[]) {
    _params = std::make_unique<Arguments>(argc, argv);
  }

  void Core::run() {
    try {
      _params->parse();
      if (_params->get_help()) {
        std::cout << USAGE << std::endl;
        return;
      }
      _network = std::make_unique<network::Network_client>(_params->get_server_port(), _params->get_client_port(), _params->get_lobby_server_port(),
          _params->get_ip());
      std::string line;
      while (std::getline(std::cin, line)) {
        struct test yh = {.a = 42, .b = "hello", .c = 89};
        _network->get_udp_client()->send <struct test> (yh, 1);
        _network->get_tcp_client()->send(line);
      }
    } catch (const std::exception &e) {
      if (strcmp(e.what(), EXCEPTION) != 0)
        std::cerr << e.what() << '\n';
      throw e;
    }
  }

  Core::~Core() {
  }

}  // namespace client
