/*
** EPITECH PROJECT, 2025
** r-type
** File description:
** TitlePatron
*/

#ifndef TITLE_PATRON_HPP_
#define TITLE_PATRON_HPP_


#include "Engine.hpp"
#include "modules/controller/components.hpp"
#include "modules/display/components.hpp"
#include "modules/controller/events.hpp"
#include "components.hpp"

class TitlePatron {
public:
    static void instanciate(zef::Engine &engine, const ecs::Entity &self,
                            float x, float y,
                            const std::string &spriteName,
                            float scale_w = 1.0f,
                            float scale_h = 1.0f) {
        engine.addEntityComponent<zef::comp::position>(self, x, y);

        zef::comp::drawable dr;
        dr.addAnimation(spriteName, 1, 200);
        dr.playAnimationLoop(spriteName, 1);
        dr.layer = 0;             
        dr.setScale(scale_w, scale_h);           
        engine.addEntityComponent<zef::comp::drawable>(self, dr);
    }
};

#endif // TITLE_PATRON_HPP_
