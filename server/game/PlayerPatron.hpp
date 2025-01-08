/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** PlayerPatron
*/

#ifndef PLAYERPATRON_HPP_
#define PLAYERPATRON_HPP_

#include <iostream>

#include "Engine.hpp"

#include "components.hpp"

#include "modules/movement/components.hpp"
#include "modules/display/components.hpp"
#include "modules/network/components.hpp"

#include "events.hpp"

#include "BulletPatron.hpp"

zef::comp::event_listener createPlayerEventListener() {
  zef::comp::event_listener evtl;

  evtl.setEvent<SetPlayerVectorEvent>([](zef::Engine& engine, size_t self,
                                         SetPlayerVectorEvent nv) {
    engine.fetchEntityComponent<VectorHolder>(self).x += nv.x;
    engine.fetchEntityComponent<VectorHolder>(self).y += nv.y;

    std::cout << engine.fetchEntityComponent<VectorHolder>(self).x << " "
              << engine.fetchEntityComponent<VectorHolder>(self).y << std::endl;
  });

  evtl.setEvent<ShootPlayerEvent>(
      [](zef::Engine& engine, size_t self, ShootPlayerEvent sht) {
        zef::comp::position& p =
            engine.fetchEntityComponent<zef::comp::position>(self);
        engine.instanciatePatron<BulletPatron>(p.x, p.y);
      });

  evtl.setEvent<CollideWithEnnemy>(
      [](zef::Engine& engine, size_t self, CollideWithEnnemy sht) {
        engine.fetchEntityComponent<Health>(self).hp = 0;
      });

  return evtl;
}

class PlayerPatron {
public:
  static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x,
                          float y, size_t rep) {
    engine.addEntityComponent<zef::comp::position>(self, x, y);
    engine.addEntityComponent<zef::comp::vector>(self, 0, 0, 10);
    engine.addEntityComponent<zef::comp::replicable>(self, rep);
    engine.addEntityComponent<VectorHolder>(self, 0.0f, 0.0f);
    engine.addEntityComponent<Player>(self);

    engine.addEntityComponent<Health>(self, 100, 100);

    zef::comp::drawable dr;
    dr.addAnimation("ship", 5, 200);
    dr.playAnimationLoop("ship", 1);
    engine.addEntityComponent<zef::comp::drawable>(self, dr);

    zef::comp::collidable coll({zef::utils::hitbox(0, 0, 60, 60)});
    engine.addEntityComponent<zef::comp::collidable>(self, coll);

    engine.addEntityComponent<zef::comp::event_listener>(
        self, createPlayerEventListener());
  }
};

#endif /* !PLAYERPATRON_HPP_ */
