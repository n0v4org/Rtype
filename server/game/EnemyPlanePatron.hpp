/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** EnemyPlanePatron
*/

#ifndef ENEMYPLANE_PATRON_HPP_
#define ENEMYPLANE_PATRON_HPP_

#include <iostream>
#include <vector>
#include "Engine.hpp"

#include "components.hpp"
#include "modules/movement/components.hpp"
#include "modules/display/components.hpp"
#include "modules/controller/components.hpp"
#include "modules/network/components.hpp"
#include "events.hpp"

inline zef::comp::event_listener creatPlaneMove() {
   zef::comp::event_listener evtl;
  
   evtl.setEvent<PlaneShootEvent>(
      [](zef::Engine& engine, size_t self, PlaneShootEvent p) {
        auto& pos = engine.fetchEntityComponent<zef::comp::position>(self);
  
        
      });
  
   evtl.setEvent<OnDeath>([](zef::Engine& engine, size_t self, OnDeath p) {
    engine.reg.kill_entity(ecs::Entity(self));
  });
  
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

class EnemyPlanePatron {
public:
  static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x,
                          float y, size_t rep) {
    engine.addEntityComponent<zef::comp::position>(self, x, y);

    engine.addEntityComponent<zef::comp::vector>(self, -5.f, 0.f, 3.f);

    engine.addEntityComponent<Health>(self, 10, 10);

    engine.addEntityComponent<zef::comp::event_listener>(self,
                                                         creatPlaneMove());

    engine.addEntityComponent<Plane>(self);

    engine.addEntityComponent<Monster>(self);

    engine.addEntityComponent<zef::comp::replicable>(self, rep);

    std::vector<zef::utils::hitbox> hb = {
        zef::utils::hitbox(0, 0, 33 * 2, 33 * 2)};
    engine.addEntityComponent<zef::comp::collidable>(self, hb);
  }
};

#endif  // ENEMYPLANE_PATRON_HPP_