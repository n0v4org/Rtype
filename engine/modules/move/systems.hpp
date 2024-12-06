/*
** EPITECH PROJECT, 2024
** leVraiRtype
** File description:
** systems
*/

#ifndef SYSTEMS_HPP_
#define SYSTEMS_HPP_

#include "../../Engine.hpp"
#include "../../ecs/sparse_array.hpp"
#include "components.hpp"
#include "../../ecs/zipper.hpp"

namespace zef {
    namespace sys {
        void move(Engine &engine, ecs::sparse_array<comp::position> &positions, ecs::sparse_array<comp::vector> &vectors) {
            for (auto &&[pos, vec] : ecs::zipper(positions, vectors)) {
                pos.x += vec.x;
                pos.y += vec.y;
            }
        }
    }
}

#endif /* !SYSTEMS_HPP_ */
