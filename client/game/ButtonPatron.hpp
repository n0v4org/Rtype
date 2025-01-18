/*
** EPITECH PROJECT, 2025
** r-type
** File description:
** ButtonPatron
*/

#ifndef BUTTON_PATRON_HPP_
#define BUTTON_PATRON_HPP_

#include <functional>
#include <string>
#include <vector>

#include "Engine.hpp"
#include "modules/controller/components.hpp"
#include "modules/display/components.hpp"
#include "modules/controller/events.hpp"
#include "components.hpp"

class ButtonPatron {
public:
    static void instanciate(zef::Engine &engine, const ecs::Entity &self,
                            float x, float y,
                            const std::string &spriteName,
                            std::function<void(zef::Engine &, size_t)> onClickCallback,
                            float width = 200.0f, float height = 100.0f, float scale_w = 1.0f,
                            float scale_h = 1.0f, float rotation = 0.0f, int layer = 1) {
        engine.addEntityComponent<zef::comp::position>(self, x, y);

        std::vector<zef::utils::hitbox> hb = {zef::utils::hitbox(0, 0, width * scale_w, height * scale_h)};
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
        dr.layer = layer;
        dr.setScale(scale_w, scale_h);
        dr.rotation =rotation;
        engine.addEntityComponent<zef::comp::drawable>(self, dr);
    }
};

class SoundBarPatron {
    public:
        static void instanciate(zef::Engine &engine, const ecs::Entity &self,
                            float x, float y) {
            engine.addEntityComponent<zef::comp::position>(self, x, y);
            engine.addEntityComponent<SounbdBar>(self);
        }
};

class TextButtonPatron {
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self,
                          float x, float y,
                          const std::string &spriteName,
                          const std::string &text, const std::string &font, int textSize,
                          std::function<void(zef::Engine &, size_t)> onClickCallback,
                          float width = 200.0f, float height = 100.0f, float scale_w = 1.0f,
                          float scale_h = 1.0f, int layer= 1) {
    engine.addEntityComponent<zef::comp::position>(self, x, y);

    std::vector<zef::utils::hitbox> hb = {zef::utils::hitbox(0, 0, width * scale_w, height * scale_h)};
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
    dr.layer = layer;
    dr.setScale(scale_w, scale_h);
    engine.addEntityComponent<zef::comp::drawable>(self, dr);

    zef::comp::drawableText txt;
    txt.layer = 999;
    txt.text = text;
    txt.font = font;
    txt.scaleX = scale_w;
    txt.scaleY = scale_h;
    txt.textSize = textSize;

    engine.addEntityComponent<zef::comp::drawableText>(self, txt);

  }
};




#endif // BUTTON_PATRON_HPP_
