/*
** EPITECH PROJECT, 2025
** RTYPE
** File description:
**
*/

#include <iostream>

#include "new.hpp"

void testSystem(ecs::sparse_array<comp1> &comps) {
  for (auto &&[c] : ecs::zipper(comps)) {
    std::cout << "TEST: "
              << "Int: " << c.in << std::endl;
  }
}

extern "C" 
#ifdef _MSC_VER
  __declspec(dllexport)
#endif
zef::IModule *entryPoint() {
  return new NewModule;
}