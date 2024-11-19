/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** main
*/

#include <iostream>

#include "macro.hpp"
#include "ServerError.hpp"

int main(void) {
  try
  {
    throw ServerError("test", SERVER_INTERNAL_ERROR);
    return OK;
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
}
