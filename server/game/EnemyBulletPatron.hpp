/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** BulletPatron
*/

#ifndef ENEMYBULLETPATRON_HPP_
#define ENEMYBULLETPATRON_HPP_

#include <vector>

#include "Engine.hpp"

#include "components.hpp"

#include "modules/movement/components.hpp"
#include "modules/movement/events.hpp"
#include "modules/display/components.hpp"
#include "BlastPatron.hpp"

#include "events.hpp"

inline zef::comp::event_listener createBulletEventListener() {
  // zef::comp::event_listener evtl;
  //
  // evtl.setEvent<zef::evt::startCollision>(
  //    [](zef::Engine& engine, size_t self, zef::evt::startCollision col) {
  //
  //    });
  //
  // evtl.setEvent<OnDeath>([](zef::Engine& engine, size_t self, OnDeath db) {
  //  float& posx = engine.fetchEntityComponent<zef::comp::position>(self).x;
  //  float& posy = engine.fetchEntityComponent<zef::comp::position>(self).y;
  //
  //  engine.instanciatePatron<BlastPatron>(posx, posy, 1.0f);
  //  engine.reg.kill_entity(ecs::Entity(self));
  //});
  //
  // evtl.setEvent<GetHittedByPlayer>(
  //    [](zef::Engine& engine, size_t self, GetHittedByPlayer p) {
  //      engine.sendEvent<OnDeath>(self);
  //    });
  //
  // evtl.setEvent<zef::evt::startCollision>(
  //    [](zef::Engine& engine, size_t self, zef::evt::startCollision p) {
  //      engine.sendEvent<GetHittedByMonsterBullet>(p.other);
  //    });
  //
  // return evtl;
}

class EnemyBulletPatron {
public:
  static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x,
                          float y, float vx, float vy) {
    engine.addEntityComponent<zef::comp::position>(self, x, y);
    engine.addEntityComponent<zef::comp::vector>(self, vx, vy, 5);
    engine.addEntityComponent<Lifetime>(self, 15000 * 1000);

    engine.addEntityComponent<zef::comp::event_listener>(
        self, createBulletEventListener());

    std::vector<zef::utils::hitbox> hb = {
        zef::utils::hitbox(0, 0, 16 * 2, 16 * 2)};
    engine.addEntityComponent<zef::comp::collidable>(self, hb);
  }
};

#endif /* !BULLETPATRON_HPP_ */
