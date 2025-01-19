/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** BlockWallPatron
*/

#ifndef BLOCKWALLPATRON_HPP_
#define BLOCKWALLPATRON_HPP_

#include <vector>
#include "Engine.hpp"

#include "components.hpp"
#include "modules/movement/components.hpp"
#include "modules/display/components.hpp"
#include "events.hpp"

class BlockWallPatron {
public:
    static void instanciate(zef::Engine& engine,
                            const ecs::Entity& self,
                            float x, float y,
                            float scaleX = 1.f, float scaleY = 1.f, float rotation = 0.f)
    {
        engine.addEntityComponent<zef::comp::position>(self, x, y);
        zef::comp::drawable dr;
        dr.addAnimation("CWall", 1, 200); 
        dr.playAnimationLoop("CWall", 1);
        dr.setScale(scaleX, scaleY);
        dr.rotation = rotation;
        engine.addEntityComponent<zef::comp::drawable>(self, dr);
        std::vector<zef::utils::hitbox> hb = {
            zef::utils::hitbox(0, 0, 48.f * scaleX, 8.f * scaleY)
        };
        engine.addEntityComponent<zef::comp::collidable>(self, hb);
        engine.addEntityComponent<zef::comp::rigidbody>(self, hb, zef::comp::rigidbody::STATIC);
        engine.addEntityComponent<zef::comp::name>(self, "BlockWall");
    }
};

#endif  // BLOCKWALLPATRON_HPP_
