/*
** EPITECH PROJECT, 2025
** RTYPE
** File description:
** BlastPatron
*/

#ifndef BLASTPATRON_HPP_
#define BLASTPATRON_HPP_

#include "Engine.hpp"

#include "components.hpp"

#include "modules/movement/components.hpp"
#include "modules/movement/events.hpp"
#include "modules/display/components.hpp"

#include "events.hpp"

class BlastPatron {
public:
  static void instanciate(zef::Engine& engine, const ecs::Entity& self, float x,
                          float y, float size) {
    engine.addEntityComponent<zef::comp::position>(self, x, y);
    engine.addEntityComponent<Lifetime>(self, 500 * 1000);

    zef::comp::drawable dr;
    dr.addAnimation("blast", 6, 100);
    dr.playAnimation("blast", 1);
    dr.setScale(size, size);
    dr.layer = 10;
    engine.addEntityComponent<zef::comp::drawable>(self, dr);
  }
};

#endif /* !BLASTPATRON_HPP_ */
