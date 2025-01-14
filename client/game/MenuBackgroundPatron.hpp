/*
** EPITECH PROJECT, 2025
** r-type
** File description:
** MenuBackgroundPatron
*/

#ifndef MENU_BACKGROUND_PATRON_HPP_
#define MENU_BACKGROUND_PATRON_HPP_

#include "Engine.hpp"
#include "components.hpp"
#include "modules/movement/components.hpp"
#include "modules/display/components.hpp" 

class MenuBackgroundPatron {
public:
    static void instanciate(zef::Engine &engine, const ecs::Entity &self) {
        engine.addEntityComponent<zef::comp::position>(self, 0.f, 0.f);

        engine.addEntityComponent<BackGround>(self);

        zef::comp::drawable dr;
        dr.addAnimation("menu", 1, 200);
        dr.playAnimationLoop("menu", 1);
        dr.layer = -6;
        dr.setScale(1.0f, 1.0f);

        engine.addEntityComponent<zef::comp::drawable>(self, dr);
    }
};

#endif // MENU_BACKGROUND_PATRON_HPP_
