/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Core
*/

#include <cstring>
#include <memory>
#include <iostream>
#include "Arguments.hpp"
#include "Core.hpp"
#include "macro.hpp"

static const char USAGE[172] = R"(
usage:
        -h: run client in help mode
        -ip <server ip>: run network client with specified server ip
        -p <port>: run newtork client in a specified port
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
      std::cout << _params->get_port() << std::endl;
      std::cout << _params->get_ip() << std::endl;
    } catch (const std::exception &e) {
      if (strcmp(e.what(), EXCEPTION) != 0)
        std::cerr << e.what() << '\n';
      throw e;
    }
  }

  Core::~Core() {
  }

}  // namespace client
