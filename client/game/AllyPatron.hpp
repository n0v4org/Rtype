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
#include "BlastPatron.hpp"

zef::comp::event_listener createAllyEventListener() {
  zef::comp::event_listener evtl;

  evtl.setEvent<SetPlayerVectorEvent>(
      [](zef::Engine& engine, size_t self, SetPlayerVectorEvent nv) {
        engine.fetchEntityComponent<VectorHolder>(self).x += nv.x;
        engine.fetchEntityComponent<VectorHolder>(self).y += nv.y;
      });

  evtl.setEvent<ShootPlayerEvent>(
      [](zef::Engine& engine, size_t self, ShootPlayerEvent sht) {
        zef::comp::position& p =
            engine.fetchEntityComponent<zef::comp::position>(self);
        engine.instanciatePatron<BulletPatron>(p.x + 70.0f, p.y,
                                               sht.size);
      });

  evtl.setEvent<GetHittedByMonsterBullet>(
      [](zef::Engine& engine, size_t self, GetHittedByMonsterBullet p) {
        engine.addEntityComponent<Damaged>(ecs::Entity(self), 100 * 1000);
      });

  evtl.setEvent<zef::evt::startCollision>(
      [](zef::Engine& engine, size_t self, zef::evt::startCollision p) {
        engine.sendEvent<GetHittedByPlayer>(p.other);
      });

  evtl.setEvent<GetHittedByMonster>(
      [](zef::Engine& engine, size_t self, GetHittedByMonster p) {
        engine.addEntityComponent<Damaged>(ecs::Entity(self), 100 * 1000);
      });

  evtl.setEvent<OnDeath>(
      [](zef::Engine& engine, size_t self, OnDeath p) {
        float& posx = engine.fetchEntityComponent<zef::comp::position>(self).x;
        float& posy = engine.fetchEntityComponent<zef::comp::position>(self).y;
        engine.instanciatePatron<BlastPatron>(posx, posy, 5.0f);
        engine.reg.kill_entity(ecs::Entity(self));
      });

  return evtl;
}

class AllyPatron {
public:
  static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x,
                          float y, size_t rep) {
    engine.addEntityComponent<zef::comp::position>(self, x, y);
    engine.addEntityComponent<zef::comp::vector>(self, 0, 0, 10);
    engine.addEntityComponent<Health>(self, 100, 100);
    engine.addEntityComponent<zef::comp::replicable>(self, rep);
    std::cout << "instancanlly: " << rep << std::endl;

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
    std::vector<zef::utils::hitbox> hb = {zef::utils::hitbox(0, 0, 33, 17)};
    engine.addEntityComponent<zef::comp::collidable>(self, hb);
  }
};

#endif /* !ALLYPATRON */
