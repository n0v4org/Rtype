/*
** EPITECH PROJECT, 2025
** leVraiRtype
** File description:
** BorderPatron
*/

#ifndef BORDERPATRON_HPP_
#define BORDERPATRON_HPP_

#include "Engine.hpp"
#include "components.hpp"
#include "modules/movement/components.hpp"

class BorderPatron {
    public:
        static void instanciate(zef::Engine &engine, const ecs::Entity &self) {
            std::vector<zef::utils::hitbox> hitboxes;
            hitboxes.push_back(zef::utils::hitbox(960, 0, 2, 1080));  //Right
            hitboxes.push_back(zef::utils::hitbox(0, -540, 1920, 2)); //Top
            hitboxes.push_back(zef::utils::hitbox(0, 540, 1920, 2));  //Bot
            engine.addEntityComponent<zef::comp::rigidbody>(self, hitboxes, zef::comp::rigidbody::STATIC);
            engine.addEntityComponent<zef::comp::position>(self, 0, 0);
            engine.addEntityComponent<zef::comp::vector>(self, 2, 0, 0);
        }
};

#endif /* !BORDERPATRON_HPP_ */
