/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** components
*/

#ifndef ENGINE_MODULES_TEXT_ZONE_COMPONENTS_HPP_
#define ENGINE_MODULES_TEXT_ZONE_COMPONENTS_HPP_

#include <map>
#include <utility>
#include <string>
#include "../../Engine.hpp"

namespace zef {
  namespace comp {

    class textZone {
    public:
      textZone() {
      }

      bool _focused = false;
      std::string _string = "";
      float _posX;
      float _posY;
      int _size = 28;
    };

  }  // namespace comp

}  // namespace zef

#endif  // ENGINE_MODULES_TEXT_ZONE_COMPONENTS_HPP_
