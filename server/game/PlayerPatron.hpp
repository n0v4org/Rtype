/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** PlayerPatron
*/

#ifndef PLAYERPATRON_HPP_
#define PLAYERPATRON_HPP_

#include "Engine.hpp"

#include "components.hpp"

#include "modules/movement/components.hpp"
#include "modules/display/components.hpp"

#include "events.hpp"

#include "BulletPatron.hpp"

zef::comp::event_listener createPlayerEventListener() {
    zef::comp::event_listener evtl;


    evtl.setEvent<SetPlayerVectorEvent>([](zef::Engine& engine, size_t self, SetPlayerVectorEvent nv) {
        engine.fetchEntityComponent<zef::comp::vector>(self).x = nv.x;
        engine.fetchEntityComponent<zef::comp::vector>(self).y = nv.y;
    });

    evtl.setEvent<ShootPlayerEvent>([](zef::Engine& engine, size_t self, ShootPlayerEvent sht) {
        zef::comp::position& p = engine.fetchEntityComponent<zef::comp::position>(self);
        engine.instanciatePatron<BulletPatron>(p.x, p.y);
    });

    evtl.setEvent<CollideWithEnnemy>([](zef::Engine& engine, size_t self, CollideWithEnnemy sht) {
        engine.fetchEntityComponent<Health>(self).hp = 0;
    });

    return evtl;
}

class PlayerPatron {
public:
    static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x, float y) {
        engine.addEntityComponent<zef::comp::position>(self, x, y);
        engine.addEntityComponent<zef::comp::vector>(self, 0, 0, 10);

        engine.addEntityComponent<Health>(self, 100, 100);

        zef::comp::drawable dr;
        dr.addAnimation("ship", 5, 200);
        dr.playAnimationLoop("ship", 1);
        engine.addEntityComponent<zef::comp::drawable>(self, dr);

        zef::comp::collidable coll({zef::utils::hitbox(0, 0, 60, 60)});
        engine.addEntityComponent<zef::comp::collidable>(self, coll);

        engine.addEntityComponent<zef::comp::event_listener>(self, createPlayerEventListener());

    }
};

#endif /* !PLAYERPATRON_HPP_ */
