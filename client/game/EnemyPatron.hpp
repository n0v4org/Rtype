/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** EnemyPatron
*/

#ifndef ENEMYPATRON_HPP_
#define ENEMYPATRON_HPP_

#include "Engine.hpp"

#include "components.hpp"

#include "modules/movement/components.hpp"
#include "modules/movement/events.hpp"
#include "modules/display/components.hpp"

#include "events.hpp"


zef::comp::event_listener createEnemyEventListener() {
    zef::comp::event_listener evtl;

    evtl.setEvent<GetHittedByBullet>([](zef::Engine& engine, size_t self, GetHittedByBullet g){
        engine.sendEvent<DestroyBullet>(g.bullet);
    });

    
    
    return evtl;
}


class EnemyPatron {
public:
    static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x, float y) {
        engine.addEntityComponent<zef::comp::position>(self, x, y);
        engine.addEntityComponent<zef::comp::vector>(self, 0, 0, 10);


        zef::comp::drawable dr;
        dr.addAnimation("ship", 5, 200);
        dr.playAnimationLoop("ship", 1);
        engine.addEntityComponent<zef::comp::drawable>(self, dr);

        engine.addEntityComponent<zef::comp::event_listener>(self, createEnemyEventListener());

        std::vector<zef::utils::hitbox> hb = {zef::utils::hitbox(0, 0, 70, 70)};
        engine.addEntityComponent<zef::comp::collidable>(self, hb);
    }
};
#endif /* !ENEMYPATRON_HPP_ */