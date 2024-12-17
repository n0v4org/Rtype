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


    evtl.setEvent<SetPlayerVectorEvent>([](zef::Engine& engine, size_t self, SetPlayerVectorEvent nv) {
        engine.fetchEntityComponent<zef::comp::vector>(self).x += nv.x;
        engine.fetchEntityComponent<zef::comp::vector>(self).y += nv.y;
    });

    evtl.setEvent<ShootPlayerEvent>([](zef::Engine& engine, size_t self, ShootPlayerEvent sht) {
        zef::comp::position& p = engine.fetchEntityComponent<zef::comp::position>(self);
        engine.instanciatePatron<BulletPatron>(p.x, p.y);
    });

    evtl.setEvent<sendingVectorEvt>([](zef::Engine& engine, size_t self, sendingVectorEvt sve) {
        engine.ClientSend<CommandMovePlayer>(MOVEPLAYER, {sve.x, sve.y});
    });


    return evtl;
}

class PlayerPatron {
public:
    static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x, float y, size_t rep) {
        engine.addEntityComponent<zef::comp::position>(self, x, y);
        engine.addEntityComponent<zef::comp::vector>(self, 0, 0, 10);


        zef::comp::drawable dr;
        dr.addAnimation("ship", 5, 200);
        dr.playAnimationLoop("ship", 1);
        engine.addEntityComponent<zef::comp::drawable>(self, dr);

        engine.addEntityComponent<zef::comp::event_listener>(self, createPlayerEventListener());

        zef::comp::controllable cont;
        cont.bindOnDown<SetPlayerVectorEvent>(zef::utils::ArrowUp, 0.0f, -1.0f);
        cont.bindOnDown<SetPlayerVectorEvent>(zef::utils::ArrowDown, 0.0f, 1.0f);
        cont.bindOnDown<SetPlayerVectorEvent>(zef::utils::ArrowRight, 1.0f, 0.0f);
        cont.bindOnDown<SetPlayerVectorEvent>(zef::utils::ArrowLeft, -1.0f, 0.0f);
        cont.bindOnRelease<ShootPlayerEvent>(zef::utils::E);


        cont.bindOnPressed<sendingVectorEvt>(zef::utils::ArrowUp, 0.0f, -1.0f);
        cont.bindOnPressed<sendingVectorEvt>(zef::utils::ArrowDown, 0.0f, 1.0f);
        cont.bindOnPressed<sendingVectorEvt>(zef::utils::ArrowRight, 1.0f, 0.0f);
        cont.bindOnPressed<sendingVectorEvt>(zef::utils::ArrowLeft, -1.0f, 0.0f);

        cont.bindOnRelease<sendingVectorEvt>(zef::utils::ArrowUp, 0.0f, 1.0f);
        cont.bindOnRelease<sendingVectorEvt>(zef::utils::ArrowDown, 0.0f, -1.0f);
        cont.bindOnRelease<sendingVectorEvt>(zef::utils::ArrowRight, -1.0f, 0.0f);
        cont.bindOnRelease<sendingVectorEvt>(zef::utils::ArrowLeft, 1.0f, 0.0f);

        engine.addEntityComponent<zef::comp::controllable>(self, cont);
        engine.addEntityComponent<Player>(self);
        engine.addEntityComponent<zef::comp::replicable>(self, rep);

    }
};

#endif /* !PLAYERPATRON_HPP_ */
