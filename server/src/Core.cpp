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

static const char USAGE[151] = R"(
usage:
        -h: run server in help mode
        -v: run server in verbose mode
        -p <port>: run server on specified port (default is 50000)
)";

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
  } catch (const std::exception& e) {
    if (strcmp(e.what(), EXCEPTION) != 0)
      std::cerr << e.what() << '\n';
    throw e;
  }
}

Core::~Core() {
}
