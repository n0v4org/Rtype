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

#include "BlastPatron.hpp"

zef::comp::event_listener createBulletEventListener(size_t size) {
  //zef::comp::event_listener evtl;
//
  //evtl.setEvent<OnDeath>([size](zef::Engine& engine, size_t self, OnDeath db) {
  //  float& posx = engine.fetchEntityComponent<zef::comp::position>(self).x;
  //  float& posy = engine.fetchEntityComponent<zef::comp::position>(self).y;
//
  //  engine.instanciatePatron<BlastPatron>(posx, posy, size == 0 ? 0.7f : 3.0f);
  //  engine.reg.kill_entity(ecs::Entity(self));
  //});
//
  //evtl.setEvent<GetHittedByMonster>(
  //    [size](zef::Engine& engine, size_t self, GetHittedByMonster p) {
  //      if (size == 0)
  //        engine.sendEvent<OnDeath>(self);
  //    });
//
  //evtl.setEvent<zef::evt::startCollision>(
  //    [](zef::Engine& engine, size_t self, zef::evt::startCollision p) {
  //      engine.sendEvent<GetHittedByBullet>(p.other);
  //    });
//
  //return evtl;
}

class BulletPatron {
public:
  static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x,
                          float y, size_t size) {
    engine.addEntityComponent<zef::comp::position>(self, x, y);
    engine.addEntityComponent<zef::comp::vector>(self, 18, 0, 18);
    engine.addEntityComponent<Lifetime>(self, 1500 * 1000);

    engine.addEntityComponent<zef::comp::event_listener>(
        self, createBulletEventListener(size));

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
