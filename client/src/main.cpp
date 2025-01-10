/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** main
*/

#include <iostream>
#include <memory>
#include <cstring>

#include "Core.hpp"
#include "macro.hpp"
#include "game.hpp"

int main(int argc, char *argv[]) {
  runClient(0, 0, "j");
  try {
    std::unique_ptr<client::Core> core =
        std::make_unique<client::Core>(argc, argv);
    core->run();
    return OK;
  } catch (const std::exception &e) {
    if (strcmp(e.what(), EXCEPTION) != 0)
      std::cerr << e.what() << '\n';
    return KO;
  }

  return OK;
  ;
}
