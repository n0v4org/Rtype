/*
** EPITECH PROJECT, 2025
** RTYPE
** File description:
**
*/

#include <iostream>

#include "new.hpp"

extern "C" zef::IModule *entryPoint() {
  return new NewModule;
}