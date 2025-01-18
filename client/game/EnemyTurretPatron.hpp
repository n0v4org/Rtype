/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** EnemyPatron
*/

#ifndef ENEMYTURRETPATRON_HPP_
#define ENEMYTURRETPATRON_HPP_

#include <vector>
#include <string>

#include "Engine.hpp"

#include "components.hpp"

#include "modules/movement/components.hpp"
#include "modules/movement/events.hpp"
#include "modules/display/components.hpp"
#include "modules/network/components.hpp"

#include "events.hpp"

zef::comp::event_listener createEnemyTurretEventListener(bool up_down,
                                                         bool left_right) {
  zef::comp::event_listener evtl;

  evtl.setEvent<TurretTurn>([up_down, left_right](zef::Engine& engine,
                                                  size_t self, TurretTurn tt) {
    engine.fetchEntityComponent<TurretTurnRate>(self).tr = tt.angle;
    size_t& cf =
        engine.fetchEntityComponent<zef::comp::drawable>(self).current_frame;
    if (left_right) {
      cf = tt.angle;
    } else {
      if (tt.angle = 0)
        cf = 5;
      if (tt.angle = 1)
        cf = 4;
      if (tt.angle = 2)
        cf = 3;
    }
  });

  return evtl;
}

class EnemyTurretPatron {
public:
  static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x,
                          float y, bool up_down, bool left_right) {
    engine.addEntityComponent<zef::comp::position>(self, x, y);
    engine.addEntityComponent<Monster>(self);
    engine.addEntityComponent<TurretTurnRate>(self);

    std::string spr = up_down ? "turretu" : "turretd";
    zef::comp::drawable dr;
    dr.addAnimation(spr, 1, 200);
    dr.playAnimationLoop(spr, 0);
    dr.setScale(3, 3);
    dr.current_frame = 0 + (left_right * 2);
    engine.addEntityComponent<zef::comp::drawable>(self, dr);

    engine.addEntityComponent<zef::comp::event_listener>(
        self, createEnemyTurretEventListener(up_down, left_right));

    std::vector<zef::utils::hitbox> hb = {
        zef::utils::hitbox(0, 0, 70 * 2, 70 * 2)};
    engine.addEntityComponent<zef::comp::collidable>(self, hb);
  }
};
#endif /* !ENEMYTURRETPATRON_HPP_ */
