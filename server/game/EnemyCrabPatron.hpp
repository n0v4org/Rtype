/*
** EPITECH PROJECT, 2025
** r-type
** File description:
** EnemyCrabPatron
*/

#ifndef ENEMYCRAB_PATRON_HPP_
#define ENEMYCRAB_PATRON_HPP_

#include <iostream>
#include <vector>
#include "Engine.hpp"

#include "components.hpp"
#include "modules/movement/components.hpp"
#include "modules/movement/events.hpp"
#include "modules/display/components.hpp"
#include "modules/controller/components.hpp"
#include "modules/network/components.hpp"
#include "events.hpp"

inline zef::comp::event_listener createCrabEventListener() {
  zef::comp::event_listener evtl;
 
   evtl.setEvent<OnDeath>([](zef::Engine& engine, size_t self, OnDeath p) {
    engine.reg.kill_entity(ecs::Entity(self));
  });
  //
  evtl.setEvent<GetHittedByBullet>(
     [](zef::Engine& engine, size_t self, GetHittedByBullet p) {
       auto& hp = engine.fetchEntityComponent<Health>(self).hp -= p.size == 0 ? 2 : 10;
      std::cout << "toucheey\n";
     });

   evtl.setEvent<zef::evt::startCollision>(
      [](zef::Engine& engine, size_t self, zef::evt::startCollision p) {
        engine.sendEvent<GetHittedByMonster>(p.other);
    });
  
  return evtl;
}

class EnemyCrabPatron {
public:
  static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x,
                          float y, size_t rep) {
    engine.addEntityComponent<zef::comp::position>(self, x, y);

    engine.addEntityComponent<zef::comp::vector>(self, 0.f, 0.f, 3.f);

    engine.addEntityComponent<Health>(self, 15, 10);

    engine.addEntityComponent<zef::comp::event_listener>(
        self, createCrabEventListener());

    engine.addEntityComponent<Monster>(self);

    engine.addEntityComponent<zef::comp::replicable>(self, rep);

    std::vector<zef::utils::hitbox> hb = {
        zef::utils::hitbox(0, 0, 34 * 2, 34 * 2)};
    engine.addEntityComponent<zef::comp::collidable>(self, hb);
  }
};

#endif  // ENEMYCRAB_PATRON_HPP_