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
#include "modules/controller/components.hpp"
#include "modules/network/components.hpp"

#include "CommonCommands.hpp"

#include "events.hpp"

#include "BulletPatron.hpp"

struct sendingVectorEvt {
  float x;
  float y;
};

zef::comp::event_listener createPlayerEventListener() {
  zef::comp::event_listener evtl;

  evtl.setEvent<SetPlayerVectorEvent>(
      [](zef::Engine& engine, size_t self, SetPlayerVectorEvent nv) {
        engine.fetchEntityComponent<zef::comp::vector>(self).x += nv.x;
        engine.fetchEntityComponent<zef::comp::vector>(self).y += nv.y;
      });

  evtl.setEvent<ShootPlayerEvent>(
      [](zef::Engine& engine, size_t self, ShootPlayerEvent sht) {
        zef::comp::position& p =
            engine.fetchEntityComponent<zef::comp::position>(self);
        size_t& ld = engine.fetchEntityComponent<Laser>(self).load;

        engine.instanciatePatron<BulletPatron>(p.x + 70.0f, p.y,
                                               ld >= 16000 * 30 ? 2 : 0);
        // engine.instanciatePatron<BulletPatron>(p.x + 80.0f, p.y, ld >= 16000
        // * 30 ? 2 : 0); engine.instanciatePatron<BulletPatron>(p.x + 90.0f,
        // p.y, ld >= 16000 * 30 ? 2 : 0);
        // engine.instanciatePatron<BulletPatron>(p.x + 100.0f, p.y, ld >= 16000
        // * 30 ? 2 : 0); engine.instanciatePatron<BulletPatron>(p.x + 110.0f,
        // p.y, ld >= 16000 * 30 ? 2 : 0);
        ld = 0;
        // engine.ClientSend<CommandShoot>(SHOOTPLAYER, {});
      });
  evtl.setEvent<LoadShoot>([](zef::Engine& engine, size_t self, LoadShoot sht) {
    engine.fetchEntityComponent<Laser>(self).load += engine.elapsed.count();
    //std::cout << engine.fetchEntityComponent<Laser>(self).load << std::endl;
    // engine.ClientSend<CommandShoot>(SHOOTPLAYER, {});
  });

  evtl.setEvent<sendingVectorEvt>(
      [](zef::Engine& engine, size_t self, sendingVectorEvt sve) {
        // engine.ClientSend<CommandMovePlayer>(MOVEPLAYER, {sve.x, sve.y});
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

class PlayerPatron {
public:
  static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x,
                          float y, size_t rep) {
    engine.addEntityComponent<zef::comp::position>(self, x, y);
    engine.addEntityComponent<zef::comp::vector>(self, 0, 0, 10);
    engine.addEntityComponent<Health>(self, 75, 100);
    engine.addEntityComponent<Laser>(self);

    //engine.addEntityComponent<Damaged>(self, 5000 * 1000);

    zef::comp::drawable dr;
    dr.addAnimation("player_0", 1, 200);
    dr.addAnimation("player_t2", 1, 200);
    dr.addAnimation("player_d2", 1, 200);
    dr.playAnimationLoop("player_0", 1);
    dr.layer = 9;
    engine.addEntityComponent<zef::comp::drawable>(self, dr);

    engine.addEntityComponent<zef::comp::event_listener>(
        self, createPlayerEventListener());

    zef::comp::controllable cont;
    cont.bindOnDown<SetPlayerVectorEvent>(zef::utils::ArrowUp, 0.0f, -10.0f);
    cont.bindOnDown<SetPlayerVectorEvent>(zef::utils::ArrowDown, 0.0f, 10.0f);
    cont.bindOnDown<SetPlayerVectorEvent>(zef::utils::ArrowRight, 10.0f, 0.0f);
    cont.bindOnDown<SetPlayerVectorEvent>(zef::utils::ArrowLeft, -10.0f, 0.0f);
    cont.bindOnDown<LoadShoot>(zef::utils::E);
    cont.bindOnRelease<ShootPlayerEvent>(zef::utils::E);
    cont.bindOnPressed<sendingVectorEvt>(zef::utils::ArrowUp, 0.0f, -10.0f);
    cont.bindOnPressed<sendingVectorEvt>(zef::utils::ArrowDown, 0.0f, 10.0f);
    cont.bindOnPressed<sendingVectorEvt>(zef::utils::ArrowRight, 10.0f, 0.0f);
    cont.bindOnPressed<sendingVectorEvt>(zef::utils::ArrowLeft, -10.0f, 0.0f);
    cont.bindOnRelease<sendingVectorEvt>(zef::utils::ArrowUp, 0.0f, 10.0f);
    cont.bindOnRelease<sendingVectorEvt>(zef::utils::ArrowDown, 0.0f, -10.0f);
    cont.bindOnRelease<sendingVectorEvt>(zef::utils::ArrowRight, -10.0f, 0.0f);
    cont.bindOnRelease<sendingVectorEvt>(zef::utils::ArrowLeft, 10.0f, 0.0f);
    engine.addEntityComponent<zef::comp::controllable>(self, cont);

    engine.addEntityComponent<Player>(self);
    engine.addEntityComponent<Ship>(self);
    engine.addEntityComponent<zef::comp::replicable>(self, rep);
    std::vector<zef::utils::hitbox> hb = {
      zef::utils::hitbox(0, 0, 33, 17)};
    engine.addEntityComponent<zef::comp::collidable>(self, hb);
  }
};

#endif /* !PLAYERPATRON_HPP_ */