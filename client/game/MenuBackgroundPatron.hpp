#ifndef MENU_BACKGROUND_PATRON_HPP_
#define MENU_BACKGROUND_PATRON_HPP_

#include "Engine.hpp"
#include "components.hpp"              // pour BackGround
#include "modules/movement/components.hpp" // pour zef::comp::position
#include "modules/display/components.hpp"   // pour zef::comp::drawable

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
