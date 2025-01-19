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

inline zef::comp::event_listener createMiniBossBulletEventListener() {
   zef::comp::event_listener evtl;
  
   
  
   return evtl;
}

class MiniBossBulletPatron {
public:
  static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x,
                          float y, float vx, float vy) {
    engine.addEntityComponent<zef::comp::position>(self, x, y);

    engine.addEntityComponent<zef::comp::vector>(self, vx, vy, 6);

    engine.addEntityComponent<Lifetime>(self, 15000 * 1000);

    engine.addEntityComponent<zef::comp::event_listener>(
        self, createMiniBossBulletEventListener());

    std::vector<zef::utils::hitbox> hb = {
        zef::utils::hitbox(0, 0, 24 * 2, 23 * 2)};
    engine.addEntityComponent<zef::comp::collidable>(self, hb);
  }
};

#endif  // MINIBOSSBULLET_PATRON_HPP_
