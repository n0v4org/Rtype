/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** systems
*/

#ifndef SYSTEMS_HPP_
#define SYSTEMS_HPP_


#include "components.hpp"
#include "Engine.hpp"


void entitycountdisplay(zef::Engine& engine) {
    std::cout << engine.reg.getEntityCount() << std::endl;
}

void lifetime_system(zef::Engine& engine, ecs::sparse_array<Lifetime>& lts) {
    for (auto &&[i, lt] : ecs::indexed_zipper(lts)) {
        lt.microsecs -= engine.elapsed.count();
        if (lt.microsecs <= 0)
            engine.reg.kill_entity(ecs::Entity(i));
    }
}




void resetPlayerMovement(zef::Engine& engine, ecs::sparse_array<zef::comp::vector>& hps, ecs::sparse_array<Player>& pys) {
    for (auto &&[i, hp, ps] : ecs::indexed_zipper(hps, pys)) {
        hp.x = 0.0;
        hp.y = 0.0;
    }
}


#endif /* !SYSTEMS_HPP_ */

