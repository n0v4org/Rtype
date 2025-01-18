/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** BossOneMiniPatron
*/

#ifndef BOSSONEMINIPATRON_HPP_
#define BOSSONEMINIPATRON_HPP_

#include <iostream>
#include <vector>
#include "Engine.hpp"

#include "components.hpp"
#include "modules/movement/components.hpp"
#include "modules/display/components.hpp"
#include "modules/controller/components.hpp"
#include "modules/network/components.hpp"
#include "events.hpp"
#include "BlastPatron.hpp"
#include "MiniBossBulletPatron.hpp"
#include "EnemyBulletPatron.hpp"

inline zef::comp::event_listener createMiniBossEventListener() {
  zef::comp::event_listener evtl;

  evtl.setEvent<MiniBossShoot>([](zef::Engine& engine, size_t self, MiniBossShoot p) {
        auto& pos = engine.fetchEntityComponent<zef::comp::position>(self);

        for (size_t i = 0; i < 5; i++)
            engine.instanciatePatron<MiniBossBulletPatron>(pos.x - 50 - (i * 80), pos.y, p.vx, p.vy);
  });

  evtl.setEvent<OnDeath>([](zef::Engine& engine, size_t self, OnDeath p) {
    auto& pos = engine.fetchEntityComponent<zef::comp::position>(self);
    engine.instanciatePatron<BlastPatron>(pos.x, pos.y, 3.0f);
    engine.reg.kill_entity(ecs::Entity(self));
  });

  return evtl;
}

class BossOneMiniPatron {
public:
  static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x,
                          float y, size_t rep) {
    engine.addEntityComponent<zef::comp::position>(self, x, y);

    engine.addEntityComponent<zef::comp::event_listener>(
        self, createMiniBossEventListener());
    zef::comp::drawable dr;
    dr.addAnimation("BossOneMini", 3, 800);
    dr.playAnimationLoop("BossOneMini", 1);
    dr.setScale(3.0f, 3.0f);
    engine.addEntityComponent<zef::comp::drawable>(self, dr);

    engine.addEntityComponent<Monster>(self);

    engine.addEntityComponent<zef::comp::replicable>(self, rep);
  }
};

#endif  // BOSSONEMINIPATRON_HPP_
