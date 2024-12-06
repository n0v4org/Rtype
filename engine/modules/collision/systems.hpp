/*
** EPITECH PROJECT, 2024
** leVraiRtype
** File description:
** move_collidables
*/

#ifndef ENGINE_SYSTEMS_CHECK_COLLIDABLES_HPP_
#define ENGINE_SYSTEMS_CHECK_COLLIDABLES_HPP_

#include "components.hpp"
#include "../move/components.hpp"
#include "../../ecs/zipper.hpp"
#include "../../Engine.hpp"
#include "events.hpp"

namespace zef {
    namespace sys {
        void check_collidables(Engine &engine, ecs::sparse_array<comp::collidable> &collidables,
            ecs::sparse_array<comp::position> &positions) {
                for (auto &&[i, col, pos] : ecs::indexed_zipper(collidables, positions)) {
                    for (auto &hitboxe : col._hitboxes) {
                        hitboxe._posX = pos.x + hitboxe._offsetX - (hitboxe._width / 2);
                        hitboxe._posY = pos.y + hitboxe._offsetY - (hitboxe._height / 2);
                    }
                }
                for (auto &&[i, col, pos] : ecs::indexed_zipper(collidables, positions)) {
                    for (auto &&[j, col2] : ecs::indexed_zipper(collidables)) {
                        if (i != j) {
                            if (col.isColliding(col2)) {
                                engine.sendEvent<evt::collision>(j);
                            }
                        }
                    }
                }

            }
    } // namespace sys
} // namespace zef

#endif // ENGINE_SYSTEMS_CHECK_COLLIDABLES_HPP_
