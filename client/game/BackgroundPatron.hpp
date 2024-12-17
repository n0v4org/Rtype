/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** BackgroundPatron
*/

#ifndef BACKGROUNDPATRON_HPP_
#define BACKGROUNDPATRON_HPP_

#include "Engine.hpp"

#include "components.hpp"

#include "modules/movement/components.hpp"
#include "modules/movement/events.hpp"
#include "modules/display/components.hpp"

#include "events.hpp"



class BackgroundPatron {
public:
    static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x, float y) {
        engine.addEntityComponent<zef::comp::position>(self, x, y);
        engine.addEntityComponent<zef::comp::vector>(self, -1, 0, 3);
        engine.addEntityComponent<BackGround>(self);

        zef::comp::drawable dr;
        dr.addAnimation("bg", 1, 200);
        dr.playAnimationLoop("bg", 1);
        dr.layer = -6;
        dr.setScale(2.0f, 2.0f);
        engine.addEntityComponent<zef::comp::drawable>(self, dr);

    }
};


#endif /* !BACKGROUNDPATRON_HPP_ */
