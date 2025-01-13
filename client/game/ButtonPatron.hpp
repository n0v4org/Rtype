/*
** EPITECH PROJECT, 2025
** r-type
** File description:
** ButtonPatron
*/

#ifndef BUTTON_PATRON_HPP_
#define BUTTON_PATRON_HPP_

#include "Engine.hpp"
#include "modules/controller/components.hpp"
#include "modules/display/components.hpp"
#include "modules/controller/events.hpp"
#include "components.hpp"
#include <functional>
#include <string>
#include <vector>

class ButtonPatron {
public:
    static void instanciate(zef::Engine &engine, const ecs::Entity &self,
                            float x, float y,
                            const std::string &spriteName,
                            std::function<void(zef::Engine &, size_t)> onClickCallback,
                            float width = 200.0f, float height = 100.0f, float scale_w = 1.0f,
                            float scale_h = 1.0f) {
        engine.addEntityComponent<zef::comp::position>(self, x, y);

        std::vector<zef::utils::hitbox> hb = {zef::utils::hitbox(0, 0, width, height)};
        engine.addEntityComponent<zef::comp::clickable>(self, hb);

        zef::comp::event_listener evtl;
        evtl.setEvent<zef::evt::LeftclickRelease>(
            [onClickCallback](zef::Engine &engine, size_t self, zef::evt::LeftclickRelease evt) {
                onClickCallback(engine, self);
            }
        );
        engine.addEntityComponent<zef::comp::event_listener>(self, evtl);

        zef::comp::drawable dr;
        dr.addAnimation(spriteName, 1, 200);
        dr.playAnimationLoop(spriteName, 1);
        dr.layer = 0;             
        dr.setScale(scale_w, scale_h);           
        engine.addEntityComponent<zef::comp::drawable>(self, dr);
    }
};

#endif // BUTTON_PATRON_HPP_