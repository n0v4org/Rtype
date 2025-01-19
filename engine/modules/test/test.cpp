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
#ifdef _MSC_VER
    __declspec(dllexport)
#endif
        zef::IModule *entryPoint() {
  return new test;
}
