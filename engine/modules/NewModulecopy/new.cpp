/*
** EPITECH PROJECT, 2025
** RTYPE
** File description:
**
*/

#include <iostream>
#ifdef _MSC_VER
#include <windows.h>
#endif

#include "new.hpp"

extern "C"
#ifndef _MSVC_VER
  __declspec(dllexport)
#endif
zef::IModule *entryPoint() {
  return new NewModuleCopy;
  // zef::AModule<
  //     zef::Component<comp1, int, float, float>
  //   > *module = new zef::AModule<
  //     zef::Component<comp1, int, float, float>
  //   >;
  //   module->addSystem<comp1>(testSystem);

  // return module;
}