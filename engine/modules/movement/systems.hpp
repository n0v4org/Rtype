/*
** EPITECH PROJECT, 2024
** leVraiRtype
** File description:
** move_collidables
*/

#ifndef ENGINE_MODULES_COLLISION_SYSTEMS_HPP_
#define ENGINE_MODULES_COLLISION_SYSTEMS_HPP_

#include <cmath>
#include <utility>

#include "components.hpp"
#include "../movement/components.hpp"
#include "../../ecs/zipper.hpp"
#include "../../Engine.hpp"
#include "events.hpp"

namespace zef {
  namespace sys {
    void move(Engine &engine, ecs::sparse_array<comp::position> &positions,
              ecs::sparse_array<comp::vector> &vectors) {
      for (auto &&[pos, vec] : ecs::zipper(positions, vectors)) {
        pos.x += vec.x;
        pos.y += vec.y;
      }
    }
    void check_collidables(Engine &engine,
                           ecs::sparse_array<comp::collidable> &collidables,
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
              auto find =
                  std::find(col._colliding.begin(), col._colliding.end(), j);
              if (find == col._colliding.end()) {
                engine.sendEvent<evt::startCollision>(i, j);
                col._colliding.push_back(j);
              }
              engine.sendEvent<evt::collision>(i, j);
            } else {
              auto find =
                  std::find(col._colliding.begin(), col._colliding.end(), j);
              if (find != col._colliding.end()) {
                col._colliding.erase(find);
              }
            }
          }
        }
      }
    }
    void check_rigidity(Engine &engine,
                        ecs::sparse_array<comp::rigidbody> &rigidbodies,
                        ecs::sparse_array<comp::position> &positions,
                        ecs::sparse_array<comp::vector> &vectors) {
      for (auto &&[i, rgdb, pos] :
           ecs::indexed_zipper(rigidbodies, positions)) {
        for (auto &hitboxe : rgdb._hitboxes) {
          hitboxe._posX = pos.x + hitboxe._offsetX - (hitboxe._width / 2);
          hitboxe._posY = pos.y + hitboxe._offsetY - (hitboxe._height / 2);
        }
      }
      for (auto &&[i, rgdb, pos, vec] :
           ecs::indexed_zipper(rigidbodies, positions, vectors)) {
        for (auto &&[j, rgdb2] : ecs::indexed_zipper(rigidbodies)) {
          if (i != j) {
            if (rgdb.isColliding(rgdb2) &&
                rgdb._rigidity_type == zef::comp::rigidbody::DYNAMIC) {
              bool pass_through = false;
              for (auto &&pass : rgdb._pass_through) {
                for (auto &&tag : rgdb2._tags) {
                  if (pass == tag) {
                    pass_through = true;
                  }
                }
              }
              if (!pass_through) {
                pos.x -= vec.x;
                pos.y -= vec.y;
              }
              // engine.sendEvent<evt::collision>(j);
            }
          }
        }
      }
    }
    void normalize_velocity_vectors(Engine &engine,
                                    ecs::sparse_array<comp::vector> &vecs) {
      for (auto &&[i, vec] : ecs::indexed_zipper(vecs)) {
        float tmpx = vec.x;
        float tmpy = vec.y;

        if (tmpx == 0 && tmpy == 0)
          continue;

        float norm = std::sqrt(std::pow(tmpx, 2) + std::pow(tmpy, 2));
        vec.x /= norm;
        vec.y /= norm;
        vec.x *= vec.norm;
        vec.y *= vec.norm;
      }
    }
  }  // namespace sys
}  // namespace zef

#endif  // ENGINE_MODULES_COLLISION_SYSTEMS_HPP_
