/*
** EPITECH PROJECT, 2025
** RTYPE
** File description:
**
*/

#include <iostream>

#include "new.hpp"

extern "C" zef::IModule *entryPoint() {
  return new NewModuleCopy;
  // zef::AModule<
  //     zef::Component<comp1, int, float, float>
  //   > *module = new zef::AModule<
  //     zef::Component<comp1, int, float, float>
  //   >;
  //   module->addSystem<comp1>(testSystem);

  // return module;
}