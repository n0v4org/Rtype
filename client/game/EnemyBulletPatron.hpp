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

#include "events.hpp"

zef::comp::event_listener createBulletEventListener() {
  zef::comp::event_listener evtl;

  evtl.setEvent<zef::evt::startCollision>(
      [](zef::Engine& engine, size_t self, zef::evt::startCollision col) {
        
      });


  return evtl;
}

class EnemyBulletPatron {
public:
  static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x,
                          float y, float vx, float vy) {
    engine.addEntityComponent<zef::comp::position>(self, x, y);
    engine.addEntityComponent<zef::comp::vector>(self, vx, vy, 5);
    engine.addEntityComponent<Lifetime>(self, 15000 * 1000);

    zef::comp::drawable dr;
    dr.addAnimation("fireball", 4, 200);
    dr.playAnimationLoop("fireball", 1);
    dr.setScale(2.0, 2.0);
    engine.addEntityComponent<zef::comp::drawable>(self, dr);

    engine.addEntityComponent<zef::comp::event_listener>(
        self, createBulletEventListener());

    
      std::vector<zef::utils::hitbox> hb = {zef::utils::hitbox(0, 0, 16, 16)};
      engine.addEntityComponent<zef::comp::collidable>(self, hb);
  }
};

#endif /* !BULLETPATRON_HPP_ */
