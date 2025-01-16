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

  evtl.setEvent<GetHittedByMonsterBullet>(
        [](zef::Engine& engine, size_t self, GetHittedByMonsterBullet p) {
            engine.addEntityComponent<Damaged>(ecs::Entity(self), 100 * 1000);
        }
    );

    evtl.setEvent<zef::evt::startCollision>(
        [](zef::Engine& engine, size_t self, zef::evt::startCollision p) {
            engine.sendEvent<GetHittedByPlayer>(p.other);
        }
    );

  return evtl;
}

class AllyPatron {
public:
  static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x,
                          float y, size_t rep) {
    engine.addEntityComponent<zef::comp::position>(self, x, y);
    engine.addEntityComponent<zef::comp::vector>(self, 0, 0, 10);
    engine.addEntityComponent<Health>(self, 45, 100);
    engine.addEntityComponent<zef::comp::replicable>(self, rep);

    zef::comp::drawable dr;
    dr.addAnimation("player_0", 1, 200);
    dr.addAnimation("player_t2", 1, 200);
    dr.addAnimation("player_d2", 1, 200);
    dr.playAnimationLoop("player_0", 1);
    dr.layer = 8;
    engine.addEntityComponent<zef::comp::drawable>(self, dr);

    engine.addEntityComponent<zef::comp::event_listener>(
        self, createAllyEventListener());
    engine.addEntityComponent<Ship>(self);
    std::vector<zef::utils::hitbox> hb = {
      zef::utils::hitbox(0, 0, 33, 17)};
    engine.addEntityComponent<zef::comp::collidable>(self, hb);
  }
};

#endif /* !ALLYPATRON */
