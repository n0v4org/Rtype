/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** RobotBulletPatron
*/

#ifndef MINIBOSSBULLETBULLET_PATRON_HPP_
#define MINIBOSSBULLETBULLET_PATRON_HPP_

#include <vector>
#include "Engine.hpp"

#include "components.hpp"
#include "modules/movement/components.hpp"
#include "modules/movement/events.hpp"
#include "modules/display/components.hpp"

#include "events.hpp"
#include "BlastPatron.hpp"

inline zef::comp::event_listener createMiniBossBulletEventListener() {
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

class MiniBossBulletPatron {
public:
  static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x,
                          float y) {
    engine.addEntityComponent<zef::comp::position>(self, x, y);

    engine.addEntityComponent<zef::comp::vector>(self, -5.0f, 0.0f, 6);

    engine.addEntityComponent<Lifetime>(self, 5000 * 1000);

    zef::comp::drawable dr;
    dr.addAnimation("miniBossBullet", 4, 150);
    dr.playAnimationLoop("miniBossBullet", 1);
    dr.setScale(2.0, 2.0);
    engine.addEntityComponent<zef::comp::drawable>(self, dr);

    engine.addEntityComponent<zef::comp::event_listener>(
        self, createMiniBossBulletEventListener());

    std::vector<zef::utils::hitbox> hb = {
        zef::utils::hitbox(0, 0, 24 * 2, 23 * 2)};
    engine.addEntityComponent<zef::comp::collidable>(self, hb);
  }
};

#endif  // MINIBOSSBULLET_PATRON_HPP_
