/*
** EPITECH PROJECT, 2024
** bootstrap
** File description:
** entitie
*/

#ifndef ENGINE_ECS_ENTITIE_HPP_
#define ENGINE_ECS_ENTITIE_HPP_

#include <cstddef>
#include "registry.hpp"

namespace ecs {
  class registry;

  class Entity {
  public:
    operator size_t() const {
      return _value;
    }

    friend class registry;

    explicit Entity(size_t val) : _value(val) {
    }
  private:
    size_t _value;
  };
}  // namespace ecs

#endif  // ENGINE_ECS_ENTITIE_HPP_
