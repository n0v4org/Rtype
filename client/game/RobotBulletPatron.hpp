/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** RobotBulletPatron
*/

#ifndef ROBOTBULLET_PATRON_HPP_
#define ROBOTBULLET_PATRON_HPP_

#include <vector>
#include "Engine.hpp"

#include "components.hpp"
#include "modules/movement/components.hpp"
#include "modules/movement/events.hpp"
#include "modules/display/components.hpp"

#include "events.hpp"
#include "BlastPatron.hpp"

inline zef::comp::event_listener createRobotBulletEventListener() {
  zef::comp::event_listener evtl;

  evtl.setEvent<OnDeath>([](zef::Engine& engine, size_t self, OnDeath db) {
    auto& pos = engine.fetchEntityComponent<zef::comp::position>(self);
    engine.instanciatePatron<BlastPatron>(pos.x, pos.y, 2.0f);

    engine.reg.kill_entity(ecs::Entity(self));
  });

  evtl.setEvent<GetHittedByPlayer>(
      [](zef::Engine& engine, size_t self, GetHittedByPlayer p) {
        engine.sendEvent<OnDeath>(self);
      });

  evtl.setEvent<zef::evt::startCollision>(
      [](zef::Engine& engine, size_t self, zef::evt::startCollision p) {
        engine.sendEvent<GetHittedByMonsterBullet>(p.other);
      });

  return evtl;
}

class RobotBulletPatron {
public:
  static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x,
                          float y) {
    engine.addEntityComponent<zef::comp::position>(self, x, y);

    engine.addEntityComponent<zef::comp::vector>(self, -5.f, 0.f, 5);

    engine.addEntityComponent<Lifetime>(self, 15000 * 1000);

    zef::comp::drawable dr;
    dr.addAnimation("robotBulletA", 2, 150);
    dr.playAnimationLoop("robotBulletA", 1);
    dr.setScale(2.0, 2.0);
    engine.addEntityComponent<zef::comp::drawable>(self, dr);

    engine.addEntityComponent<zef::comp::event_listener>(
        self, createRobotBulletEventListener());

    std::vector<zef::utils::hitbox> hb = {
        zef::utils::hitbox(0, 0, 65 * 2, 17 * 2)};
    engine.addEntityComponent<zef::comp::collidable>(self, hb);
  }
};

#endif  // ROBOTBULLET_PATRON_HPP_
