/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** BulletPatron
*/

#ifndef BULLETPATRON_HPP_
#define BULLETPATRON_HPP_

#include <vector>

#include "Engine.hpp"

#include "components.hpp"

#include "modules/movement/components.hpp"
#include "modules/movement/events.hpp"
#include "modules/display/components.hpp"

#include "events.hpp"

zef::comp::event_listener createBulletEventListener() {
  zef::comp::event_listener evtl;

  evtl.setEvent<zef::evt::startCollision>(
      [](zef::Engine& engine, size_t self, zef::evt::startCollision col) {
        engine.sendEvent<GetHittedByBullet>(col.other, self, 10);
        engine.reg.kill_entity(ecs::Entity(self));
      });

  evtl.setEvent<DestroyBullet>(
      [](zef::Engine& engine, size_t self, DestroyBullet db) {
        engine.reg.kill_entity(ecs::Entity(self));
      });

  return evtl;
}

class BulletPatron {
public:
  static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x,
                          float y, size_t size) {
    engine.addEntityComponent<zef::comp::position>(self, x, y);
    engine.addEntityComponent<zef::comp::vector>(self, 1, 0, 18);
    engine.addEntityComponent<Lifetime>(self, 1500 * 1000);

    zef::comp::drawable dr;
    if (size == 2) {
      dr.addAnimation("bullet2", 2, 200);
      dr.playAnimationLoop("bullet2", 1);
      dr.setScale(3.0, 3.0);
    }
    if (size == 0) {
      dr.addAnimation("bullet", 2, 200);
      dr.playAnimationLoop("bullet", 1);
    }
    engine.addEntityComponent<zef::comp::drawable>(self, dr);

    engine.addEntityComponent<zef::comp::event_listener>(
        self, createBulletEventListener());

    if (size == 0) {
      std::vector<zef::utils::hitbox> hb = {zef::utils::hitbox(0, 0, 20, 20)};
      engine.addEntityComponent<zef::comp::collidable>(self, hb);
    }
    if (size == 2) {
      std::vector<zef::utils::hitbox> hb = {zef::utils::hitbox(0, 0, 150, 45)};
      engine.addEntityComponent<zef::comp::collidable>(self, hb);
    }
  }
};

#endif /* !BULLETPATRON_HPP_ */
