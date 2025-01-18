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
#include "modules/display/components.hpp"
#include "modules/controller/components.hpp"
#include "modules/network/components.hpp"
#include "events.hpp"
#include "BlastPatron.hpp"

inline zef::comp::event_listener createCrabEventListener() {
  zef::comp::event_listener evtl;

  evtl.setEvent<SetEnemyVectorEvent>(
      [](zef::Engine& engine, size_t self, SetEnemyVectorEvent e) {
        auto& vec      = engine.fetchEntityComponent<zef::comp::vector>(self);
        auto& draw     = engine.fetchEntityComponent<zef::comp::drawable>(self);
        vec.x          = e.vx;
        vec.y          = e.vy;
        float angleRad = std::atan2(-vec.x, vec.y);
        float angleDeg = angleRad * 180.f / static_cast<float>(M_PI);
        if (angleDeg < 0)
          angleDeg += 360.f;
        angleDeg += 270.f;
        if (angleDeg >= 360.f)
          angleDeg -= 360.f;
        std::cout << angleDeg << std::endl;
        draw.rotation = angleDeg;
      });

  evtl.setEvent<SetEnemyPos>(
      [](zef::Engine& engine, size_t self, SetEnemyPos p) {
        auto& pos = engine.fetchEntityComponent<zef::comp::position>(self);
        pos.x     = p.px;
        pos.y     = p.py;
      });

  evtl.setEvent<OnDeath>([](zef::Engine& engine, size_t self, OnDeath p) {
    auto& pos = engine.fetchEntityComponent<zef::comp::position>(self);
    engine.instanciatePatron<BlastPatron>(pos.x, pos.y, 3.0f);
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

class EnemyCrabPatron {
public:
  static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x,
                          float y, size_t rep) {
    engine.addEntityComponent<zef::comp::position>(self, x, y);

    engine.addEntityComponent<zef::comp::vector>(self, 0.f, 3.f, 3.f);

    engine.addEntityComponent<Health>(self, 25, 25);

    engine.addEntityComponent<zef::comp::event_listener>(
        self, createCrabEventListener());

    zef::comp::drawable dr;
    dr.addAnimation("enemyCrab", 1, 200);
    dr.playAnimationLoop("enemyCrab", 1);
    dr.setScale(3.0f, 3.0f);
    engine.addEntityComponent<zef::comp::drawable>(self, dr);

    engine.addEntityComponent<Monster>(self);

    engine.addEntityComponent<zef::comp::replicable>(self, rep);

    std::vector<zef::utils::hitbox> hb = {
        zef::utils::hitbox(0, 0, 34 * 2, 34 * 2)};
    engine.addEntityComponent<zef::comp::collidable>(self, hb);
  }
};

#endif  // ENEMYCRAB_PATRON_HPP_