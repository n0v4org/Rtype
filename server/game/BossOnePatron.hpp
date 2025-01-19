/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** BossOnePatron
*/

#ifndef BOSSONEPATRON_HPP_
#define BOSSONEPATRON_HPP_

#include <iostream>
#include <vector>
#include "Engine.hpp"

#include "components.hpp"
#include "modules/movement/components.hpp"
#include "modules/display/components.hpp"
#include "modules/controller/components.hpp"
#include "modules/network/components.hpp"
#include "events.hpp"
#include "BossOneMiniPatron.hpp"

inline zef::comp::event_listener createBossOneEventListener() {
   zef::comp::event_listener evtl;
  
   
  
   evtl.setEvent<OnDeath>([](zef::Engine& engine, size_t self, OnDeath p) {
    auto& pos = engine.fetchEntityComponent<zef::comp::position>(self);
    engine.reg.kill_entity(ecs::Entity(self));
  });
  
   evtl.setEvent<GetHittedByBullet>(
      [](zef::Engine& engine, size_t self, GetHittedByBullet p) {
        engine.fetchEntityComponent<Health>(self).hp -= p.size == 0 ? 2 : 10;
      });
  
   evtl.setEvent<zef::evt::startCollision>(
      [](zef::Engine& engine, size_t self, zef::evt::startCollision p) {
        engine.sendEvent<GetHittedByMonster>(p.other);
      });
  
   return evtl;
}

class BossOnePatron {
public:
  static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x,
                          float y, size_t rep) {
    engine.addEntityComponent<zef::comp::position>(self, x, y);

    engine.addEntityComponent<zef::comp::vector>(self, 0.f, 0.f, 0.f);

    engine.addEntityComponent<Health>(self, 400, 400);

    engine.addEntityComponent<zef::comp::event_listener>(
        self, createBossOneEventListener());

    engine.addEntityComponent<Monster>(self);

    engine.addEntityComponent<zef::comp::replicable>(self, rep);

    std::vector<zef::utils::hitbox> hb = {
        zef::utils::hitbox(0, 0, 161 * 2, 212 * 3)};
    engine.addEntityComponent<zef::comp::collidable>(self, hb);
    ecs::Entity miniboss =
        engine.instanciatePatron<BossOneMiniPatron>(x + 25, x / 3 - 150, 2);

        engine.addEntityComponent<Boss>(self);


  }
};

#endif  // BOSSONEPATRON_HPP_
