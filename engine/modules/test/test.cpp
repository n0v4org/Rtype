/*
** EPITECH PROJECT, 2025
** RTYPE
** FILE description:
** Module test
*/

#include "test.hpp"
#ifdef _MSC_VER
#include <windows.h>
#endif

extern "C"
#ifndef _MSVC_VER
  __declspec(dllexport)
#endif
zef::IModule *entryPoint() {
  return new test;
}
