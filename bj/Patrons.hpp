/*
** EPITECH PROJECT, 2025
** RTYPE
** File description:
** Patrons
*/

#ifndef PATRONS_HPP_
#define PATRONS_HPP_

#include "Engine.hpp"

#include "modules/display/components.hpp"
#include "modules/movement/components.hpp"
#include "modules/controller/components.hpp"

class BackGroundPatron {
    public:
        static void instanciate(zef::Engine& engine, const ecs::Entity& self) {
            engine.addEntityComponent<zef::comp::position>(self,0.0f, 0.0f);


            zef::comp::drawable dr;
            dr.addAnimation("backGround", 1, 1);
            dr.playAnimationLoop("backGround", 1.0f);
            dr.layer = -6;
            engine.addEntityComponent<zef::comp::drawable>(self, dr);
        }
};

class BackGroundGamePatron {
    public:
        static void instanciate(zef::Engine& engine, const ecs::Entity& self) {
            engine.addEntityComponent<zef::comp::position>(self,0.0f, 0.0f);


            zef::comp::drawable dr;
            dr.addAnimation("bjbg", 1, 1);
            dr.playAnimationLoop("bjbg", 1.0f);
            dr.layer = -6;
            dr.setScale(2, 2);
            engine.addEntityComponent<zef::comp::drawable>(self, dr);
        }
};

class ButtonPatron {
    public:
        static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x, float y) {
            engine.addEntityComponent<zef::comp::position>(self,x, y);


            zef::comp::drawable dr;
            dr.addAnimation("bttn", 1, 1);
            dr.playAnimationLoop("bttn", 1.0f);
            engine.addEntityComponent<zef::comp::drawable>(self, dr);
            

            std::vector<zef::utils::hitbox> hb = {zef::utils::hitbox(0, 0, 200, 100)};
            engine.addEntityComponent<zef::comp::clickable>(self, hb);


            zef::comp::event_listener evtl;

            evtl.setEvent<zef::evt::LeftclickRelease>([](zef::Engine& engine, size_t self, zef::evt::LeftclickRelease evt) {
                engine.loadScene("game");
            });

            engine.addEntityComponent<zef::comp::event_listener>(self, evtl);
        }
};

class CardPatron {
    public:
        static void instanciate(zef::Engine& engine, const ecs::Entity& self, int number, int color) {
            engine.addEntityComponent<zef::comp::position>(self, 0.0f, 0.0f);


            zef::comp::drawable dr;
            dr.addAnimation("card " + std::to_string(number) + " " + std::to_string(color), 1, 1);
            dr.playAnimationLoop("card " + std::to_string(number) + " " + std::to_string(color), 1.0f);
            engine.addEntityComponent<zef::comp::drawable>(self, dr);
        }

};




#endif /* !PATRONS_HPP_ */
