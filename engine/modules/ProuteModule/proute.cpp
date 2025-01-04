/*
** EPITECH PROJECT, 2025
** RTYPE
** File description:
** proute
*/

#include "proute.hpp"


  extern "C" zef::IModule* entryPoint() {

    return new ProuteModule;

    /*return new zef::AModule<
        zef::Component<proute, int, float, double>
      >;*/
  }