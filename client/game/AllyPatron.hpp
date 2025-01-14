/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** PlayerPatron
*/

#ifndef ALLYPATRON
#define ALLYPATRON

#include <vector>

#include "Engine.hpp"

#include "components.hpp"

#include "modules/movement/components.hpp"
#include "modules/display/components.hpp"
#include "modules/network/components.hpp"

#include "events.hpp"

#include "BulletPatron.hpp"

zef::comp::event_listener createAllyEventListener() {
  zef::comp::event_listener evtl;

  evtl.setEvent<SetPlayerVectorEvent>(
      [](zef::Engine& engine, size_t self, SetPlayerVectorEvent nv) {
        engine.fetchEntityComponent<VectorHolder>(self).x += nv.x;
        engine.fetchEntityComponent<VectorHolder>(self).y += nv.y;
      });

  evtl.setEvent<ShootPlayerEvent>(
      [](zef::Engine& engine, size_t self, ShootPlayerEvent sht) {

      });

  return evtl;
}

class AllyPatron {
public:
  static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x,
                          float y) {
    engine.addEntityComponent<zef::comp::position>(self, x, y);
    engine.addEntityComponent<zef::comp::vector>(self, 0, 0, 10);
    engine.addEntityComponent<Health>(self, 45, 100);

    zef::comp::drawable dr;
    dr.addAnimation("player_0", 1, 200);
    dr.addAnimation("player_t2", 1, 200);
    dr.addAnimation("player_d2", 1, 200);
    dr.playAnimationLoop("player_0", 1);
    engine.addEntityComponent<zef::comp::drawable>(self, dr);

    engine.addEntityComponent<zef::comp::event_listener>(
        self, createAllyEventListener());
    engine.addEntityComponent<Ship>(self);
  }
};

#endif /* !ALLYPATRON */
