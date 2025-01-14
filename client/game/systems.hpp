/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** systems
*/

#ifndef SYSTEMS_HPP_
#define SYSTEMS_HPP_

#include <iostream>

#include "components.hpp"
#include "Engine.hpp"

void entitycountdisplay(zef::Engine& engine) {
  std::cout << engine.reg.getEntityCount() << std::endl;
}

void lifetime_system(zef::Engine& engine, ecs::sparse_array<Lifetime>& lts) {
  for (auto&& [i, lt] : ecs::indexed_zipper(lts)) {
    lt.microsecs -= engine.elapsed.count();
    if (lt.microsecs <= 0) {
      engine.sendEvent<OnDeath>(i);
      // engine.reg.kill_entity(ecs::Entity(i));
    }
  }
}

void resetPlayerMovement(zef::Engine& engine,
                         ecs::sparse_array<zef::comp::vector>& hps,
                         ecs::sparse_array<Player>& pys) {
  for (auto&& [i, hp, ps] : ecs::indexed_zipper(hps, pys)) {
    hp.x = 0.0;
    hp.y = 0.0;
  }
}

void handleBackgroundScroll(zef::Engine& engine,
                            ecs::sparse_array<BackGround>& bgs,
                            ecs::sparse_array<zef::comp::position>& poss) {
  for (auto&& [i, bg, pos] : ecs::indexed_zipper(bgs, poss)) {
    if (pos.x == -1920) {
      pos.x = 1920.0f;
    }
  }
}

void drawHpBarPlayer(zef::Engine& engine, ecs::sparse_array<Ship>& pls,
                     ecs::sparse_array<Health>& hts,
                     ecs::sparse_array<zef::comp::position>& pss) {
  for (auto&& [i, p, ht, pos] : ecs::indexed_zipper(pls, hts, pss)) {
    float value = static_cast<float>(ht._hp) / static_cast<float>(ht._max);
    engine.GraphLib->drawHPBar(pos.x - 40, pos.y + 40, 80.0f, 5, value,
                               {255, 0, 0, 255}, {0, 255, 0, 255});
  }
}

void drawLoadBar(zef::Engine& engine, ecs::sparse_array<Player>& pls,
                 ecs::sparse_array<Laser>& lss,
                 ecs::sparse_array<zef::comp::position>& pss) {
  for (auto&& [i, p, ls, pos] : ecs::indexed_zipper(pls, lss, pss)) {
    float value = ls.load;
    if (value > 16000 * 30)
      value = 16000 * 30;
    value = value / static_cast<float>(16000 * 30);
    engine.GraphLib->drawHPBar(pos.x - 40, pos.y + 50, 80.0f, 5, value,
                               {0, 0, 0, 255}, {0, 0, 200, 255});
  }
}

void animateShips(zef::Engine& engine, ecs::sparse_array<Ship>& pls,
                  ecs::sparse_array<zef::comp::vector>& vcs,
                  ecs::sparse_array<zef::comp::drawable>& drs) {
  for (auto&& [i, p, vc, dr] : ecs::indexed_zipper(pls, vcs, drs)) {
    if (vc.y < 0)
      dr.playAnimationLoop("player_d2", 1);
    if (vc.y > 0)
      dr.playAnimationLoop("player_t2", 1);
    if (vc.y == 0)
      dr.playAnimationLoop("player_0", 1);
  }
}

void autoWalkShips(zef::Engine& engine, ecs::sparse_array<Ship>& shs,
                   ecs::sparse_array<zef::comp::position>& pss) {
  for (auto&& [i, p, pos] : ecs::indexed_zipper(shs, pss)) {
    pos.x += 2;
  }
}

inline void convertHolderToVect(zef::Engine& engine,
                                ecs::sparse_array<VectorHolder>& vhs,
                                ecs::sparse_array<zef::comp::vector>& vvs) {
  for (auto&& [i, vh, vc] : ecs::indexed_zipper(vhs, vvs)) {
    vc.x = vh.x;
    vc.y = vh.y;
  }
}

#endif /* !SYSTEMS_HPP_ */
