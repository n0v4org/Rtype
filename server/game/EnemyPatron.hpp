/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** EnemyPatron
*/

#ifndef ENEMYPATRON_HPP_
#define ENEMYPATRON_HPP_

#include <vector>

#include "Engine.hpp"

#include "components.hpp"

#include "modules/movement/components.hpp"
#include "modules/movement/events.hpp"
#include "modules/display/components.hpp"

#include "events.hpp"

inline zef::comp::event_listener createEnemyEventListener() {
  zef::comp::event_listener evtl;

  evtl.setEvent<GetHittedByBullet>(
      [](zef::Engine& engine, size_t self, GetHittedByBullet g) {
        engine.fetchEntityComponent<Health>(self).hp -= g.damage;
        engine.sendEvent<DestroyBullet>(g.bullet);
      });

  evtl.setEvent<zef::evt::startCollision>(
      [](zef::Engine& engine, size_t self, zef::evt::startCollision g) {
        engine.sendEvent<CollideWithEnnemy>(g.other);
      });

  return evtl;
}

class EnemyPatron {
public:
  static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x,
                          float y, size_t rep) {
    engine.addEntityComponent<zef::comp::position>(self, x, y);
    engine.addEntityComponent<zef::comp::vector>(self, -1, 0, 5);
    engine.addEntityComponent<zef::comp::replicable>(self, rep);
    engine.addEntityComponent<Health>(self, 100, 100);
    engine.addEntityComponent<Monster>(self);
    engine.addEntityComponent<Lifetime>(self, 10 * 1000 * 1000);

    zef::comp::drawable dr;
    dr.addAnimation("ship", 5, 200);
    dr.playAnimationLoop("ship", 1);
    dr.setScale(2.0, 2.0);
    engine.addEntityComponent<zef::comp::drawable>(self, dr);

    engine.addEntityComponent<zef::comp::event_listener>(
        self, createEnemyEventListener());

    std::vector<zef::utils::hitbox> hb = {
        zef::utils::hitbox(0, 0, 70 * 2, 70 * 2)};
    engine.addEntityComponent<zef::comp::collidable>(self, hb);
  }
};
#endif /* !ENEMYPATRON_HPP_ */
