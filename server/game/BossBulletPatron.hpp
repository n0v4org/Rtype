/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** RobotBulletPatron
*/

#ifndef BOSSBULLETBULLET_PATRON_HPP_
#define BOSSBULLETBULLET_PATRON_HPP_

#include <vector>
#include "Engine.hpp"

#include "components.hpp"
#include "modules/movement/components.hpp"
#include "modules/movement/events.hpp"
#include "modules/display/components.hpp"

#include "events.hpp"
#include "BlastPatron.hpp"

inline zef::comp::event_listener createBossBulletEventListener() {
   zef::comp::event_listener evtl;
  
   evtl.setEvent<OnDeath>([](zef::Engine& engine, size_t self, OnDeath db) {
    auto& pos = engine.fetchEntityComponent<zef::comp::position>(self);
    engine.instanciatePatron<BlastPatron>(pos.x, pos.y, 2.0f);
  
    engine.reg.kill_entity(ecs::Entity(self));
  });
  
   evtl.setEvent<GetHittedByBullet>(
      [](zef::Engine& engine, size_t self, GetHittedByBullet p) {
        engine.addEntityComponent<Damaged>(ecs::Entity(self), 100 * 1000);
      });
  
   evtl.setEvent<zef::evt::startCollision>(
      [](zef::Engine& engine, size_t self, zef::evt::startCollision p) {
        engine.sendEvent<GetHittedByMonster>(p.other);
      });
  
   return evtl;
}

class BossBulletPatron {
public:
  static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x,
                          float y, float vx, float vy) {
    engine.addEntityComponent<zef::comp::position>(self, x, y);

    engine.addEntityComponent<zef::comp::vector>(self, vx, vy, 6);

    engine.addEntityComponent<Lifetime>(self, 15000 * 1000);

    engine.addEntityComponent<zef::comp::event_listener>(
        self, createBossBulletEventListener());

    std::vector<zef::utils::hitbox> hb = {
        zef::utils::hitbox(0, 0, 18 * 3, 18 * 3)};
    engine.addEntityComponent<zef::comp::collidable>(self, hb);
  }
};

#endif  // BOSSBULLET_PATRON_HPP_
