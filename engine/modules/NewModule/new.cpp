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
    std::cout << "TEST: " << "Int: " << c.in << std::endl;
  }
}


extern "C" zef::IModule* entryPoint() {
  return new NewModule;
  // zef::AModule<
  //     zef::Component<comp1, int, float, float>
  //   > *module = new zef::AModule<
  //     zef::Component<comp1, int, float, float>
  //   >;
  //   module->addSystem<comp1>(testSystem);

  // return module;
}