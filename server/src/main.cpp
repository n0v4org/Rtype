/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** main
*/

#include <iostream>
#include <memory>

#include "macro.hpp"
#include "Core.hpp"
#include "ServerError.hpp"
#include "macro.hpp"

int main(int argc, char *argv[]) {
  try
  {
    std::unique_ptr<Core> core = std::make_unique<Core>(argv, argc);
    core->run();
  }
  catch(const std::exception& e)
  {
    if (strcmp(e.what(), EXCEPTION) != 0)
      std::cerr << e.what() << '\n';
    return ERROR;
  }
  return OK;
}
