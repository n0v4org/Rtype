/*
** EPITECH PROJECT, 2024
** leVraiRtype
** File description:
** collision
*/

#ifndef ENGIN_EVENTS_COLLISION_HPP_
#define ENGIN_EVENTS_COLLISION_HPP_

#include "../ecs/entitie.hpp"

namespace zef {
    namespace evt {
        struct collision {
            size_t other;
        };
    } // namespace evt
} // namespace zef

#endif // ENGIN_EVENTS_COLLISION_HPP_
