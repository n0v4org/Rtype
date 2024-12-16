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
#include "Lobby.hpp"
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
      // _tcp_client = std::make_shared<network::lobby::Client>(
      //     _io_service, _params->get_ip(), _params->get_lobby_server_port());
      // _tcp_client->start();
      // std::thread t([this]() { _io_service.run(); });
      // std::string line;
      // while (std::getline(std::cin, line)) {
      //   _tcp_client->write(line);
      //   while (1) {
      //     std::string tmp = _tcp_client->fetchLatestMessage();
      //     if (tmp.empty())
      //       break;
      //     else
      //       std::cout << tmp << std::endl;
      //   }
      //   std::cout << "here" << _tcp_client->fetchLatestMessage() << std::endl;
      //   if (line.compare(0, 11, "LAUNCH_GAME") == 0)
      //     break;
      // }
      // std::string port;
      // while (1) {
      //   port = _tcp_client->fetchLatestMessage();
      //   if (!port.empty()) {
      //     if (port.find(":") != std::string::npos) {
      //       port = port.substr(port.find(":"), port.length() - port.find(":"));
      //     }
      //     break;
      //   }
      // }
      // std::cout << "aqui" << std::endl;
      _client = std::make_unique<network::game::Client>(_params->get_server_port(),
                                              _params->get_client_port(),
                                              _params->get_ip(),
                                              _io_service);
      std::string line;
       while (std::getline(std::cin, line)) {
        input_t test = {
          .cmd = 1,
          .payload_size = sizeof(struct test),
          .seq = 2,
          .payload = {0}
        };
        struct test yh = {
          .a = 42,
          .b = "hello",
          .c = 89
        };
        _client->send(network::game::Commands<struct test>::toArray(yh, test));
      }
      // t.join();
    } catch (const std::exception &e) {
      if (strcmp(e.what(), EXCEPTION) != 0)
        std::cerr << e.what() << '\n';
      throw e;
    }
  }

  Core::~Core() {
  }

}  // namespace client
