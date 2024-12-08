/*
** EPITECH PROJECT, 2024
** leVraiRtype
** File description:
** move_collidables
*/

#ifndef ENGINE_MODULES_COLLISION_SYSTEMS_HPP_
#define ENGINE_MODULES_COLLISION_SYSTEMS_HPP_

#include "components.hpp"
#include "../movement/components.hpp"
#include "../../ecs/zipper.hpp"
#include "../../Engine.hpp"
#include "events.hpp"

namespace zef {
    namespace sys {
        void move(Engine &engine, ecs::sparse_array<comp::position> &positions, ecs::sparse_array<comp::vector> &vectors) {
            for (auto &&[pos, vec] : ecs::zipper(positions, vectors)) {
                pos.x += vec.x;
                pos.y += vec.y;
            }
        }
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
        void check_rigidity(Engine &engine, ecs::sparse_array<comp::rigidbody> &rigidbodies,
            ecs::sparse_array<comp::position> &positions,
            ecs::sparse_array<comp::vector> &vectors) {
                for (auto &&[i, rgdb, pos] : ecs::indexed_zipper(rigidbodies, positions)) {
                    for (auto &hitboxe : rgdb._hitboxes) {
                        hitboxe._posX = pos.x + hitboxe._offsetX - (hitboxe._width / 2);
                        hitboxe._posY = pos.y + hitboxe._offsetY - (hitboxe._height / 2);
                    }
                }
                for (auto &&[i, rgdb, pos, vec] : ecs::indexed_zipper(rigidbodies, positions, vectors)) {
                    for (auto &&[j, rgdb2] : ecs::indexed_zipper(rigidbodies)) {
                        if (i != j) {
                            if (rgdb.isColliding(rgdb2) && rgdb._rigidity_type == zef::comp::rigidbody::DYNAMIC) {
                                pos.x -= vec.x;
                                pos.y -= vec.y;
                                //engine.sendEvent<evt::collision>(j);
                            }
                        }
                    }
                }

            }
    } // namespace sys
} // namespace zef

#endif // ENGINE_MODULES_COLLISION_SYSTEMS_HPP_
