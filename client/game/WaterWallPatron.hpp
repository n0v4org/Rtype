/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** WaterWallPatron
*/

#ifndef WATERWALLPATRON_HPP_
#define WATERWALLPATRON_HPP_

#include <vector>
#include "Engine.hpp"

#include "components.hpp"               
#include "modules/movement/components.hpp" 
#include "modules/display/components.hpp"  
#include "events.hpp"                   

class WaterWallPatron {
public:
    static void instanciate(zef::Engine& engine,
                            const ecs::Entity& self,
                            float x, float y,
                            float scaleX = 1.f, float scaleY = 1.f, float rotation = 0.f)
    {
        engine.addEntityComponent<zef::comp::position>(self, x, y);
        zef::comp::drawable dr;
        dr.addAnimation("BWall", 1, 200); 
        dr.playAnimationLoop("BWall", 1);
        dr.setScale(scaleX, scaleY);
        dr.rotation = rotation;
        engine.addEntityComponent<zef::comp::drawable>(self, dr);
        std::vector<zef::utils::hitbox> hb = {
            zef::utils::hitbox(0, 0, 48.f * scaleX, 8.f * scaleY)
        };
        engine.addEntityComponent<zef::comp::collidable>(self, hb);
        engine.addEntityComponent<zef::comp::rigidbody>(self, hb, zef::comp::rigidbody::STATIC);
        engine.addEntityComponent<zef::comp::name>(self, "WaterWall");
    }
};

#endif // WATERWALLPATRON_HPP_
