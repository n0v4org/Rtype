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
      // _client = std::make_unique<net::Client>(_params->get_server_port(),
      //                                         _params->get_client_port(),
      //                                         _params->get_ip(), _io_service);
      _tcp_client = std::make_shared<network::lobby::Client>( _io_service, 
                                              _params->get_ip(), _params->get_lobby_server_port());
      _tcp_client->start();
      std::thread t([this]() { _io_service.run(); });
      std::string line;
      while (std::getline(std::cin, line)) {
        _tcp_client->write(line);
      }
      t.join();
    } catch (const std::exception &e) {
      if (strcmp(e.what(), EXCEPTION) != 0)
        std::cerr << e.what() << '\n';
      throw e;
    }
  }

  Core::~Core() {
  }

}  // namespace client
