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

inline zef::comp::event_listener createAllyEventListener() {
   zef::comp::event_listener evtl;
  
  

  
   evtl.setEvent<GetHittedByMonsterBullet>(
      [](zef::Engine& engine, size_t self, GetHittedByMonsterBullet p) {
        engine.fetchEntityComponent<Health>(self).hp -= 10;
        engine.fetchEntityComponent<Health>(self).up = true;
      });
  
   evtl.setEvent<zef::evt::startCollision>(
      [](zef::Engine& engine, size_t self, zef::evt::startCollision p) {
        engine.sendEvent<GetHittedByPlayer>(p.other);
      });
  
   evtl.setEvent<GetHittedByMonster>(
      [](zef::Engine& engine, size_t self, GetHittedByMonster p) {
        engine.fetchEntityComponent<Health>(self).hp -= 1;
      });
   evtl.setEvent<OnDeath>(
      [](zef::Engine& engine, size_t self, OnDeath p) {
        engine.reg.kill_entity(ecs::Entity(self));
      });
  
   return evtl;
}

class AllyPatron {
public:
  static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x,
                          float y, size_t rep) {
    std::cout << "planeeeeeeee" << std::endl;
    engine.addEntityComponent<zef::comp::position>(self, x, y);
    std::cout << "planeeeeeeee1" << std::endl;
    engine.addEntityComponent<zef::comp::vector>(self, 0, 0, 10);
    std::cout << "planeeeeeeee2" << std::endl;
    engine.addEntityComponent<Health>(self, 100, 100);
    std::cout << "planeeeeeeee3" << std::endl;
    engine.addEntityComponent<zef::comp::replicable>(self, rep);
    std::cout << "planeeeeeeee4" << std::endl;

    engine.addEntityComponent<zef::comp::event_listener>(self, createAllyEventListener());
    std::cout << "planeeeeeeee5" << std::endl;
    engine.addEntityComponent<Ship>(self);
    std::cout << "planeeeeeeee6" << std::endl;
    std::vector<zef::utils::hitbox> hb = {zef::utils::hitbox(0, 0, 33, 17)};
    std::cout << "planeeeeeeee7" << std::endl;
    engine.addEntityComponent<zef::comp::collidable>(self, hb);
  }
};

#endif /* !ALLYPATRON */
