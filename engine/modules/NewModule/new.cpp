/*
** EPITECH PROJECT, 2025
** RTYPE
** File description:
** 
*/

#include "new.hpp"

extern "C" zef::IModule* entryPoint() {
  return new NewModule;

  /*return new zef::AModule<
      zef::Component<proute, int, float, double>
    >;*/
}