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


void handleHealth(zef::Engine& engine, ecs::sparse_array<Health>& hps) {
    for (auto &&[i, hp] : ecs::indexed_zipper(hps)) {
        if (hp.hp <= 0)
            engine.reg.kill_entity(ecs::Entity(i));
    }
}

void convertHolderToVect(zef::Engine& engine, ecs::sparse_array<VectorHolder>& vhs, ecs::sparse_array<zef::comp::vector>& vvs) {
    for (auto &&[i, vh, vc] : ecs::indexed_zipper(vhs, vvs)) {
        vc.x = vh.x;
        vc.y = vh.y;
    }
}


#endif /* !SYSTEMS_HPP_ */

