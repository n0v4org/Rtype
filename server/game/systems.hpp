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
#include "CommonCommands.hpp"


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

void syncPlayers(zef::Engine& engine, ecs::sparse_array<PlayerReplacer>& prs) {
    for (auto &&[pr] : ecs::zipper(prs)) {
        pr.time += engine.elapsed.count();

        if (pr.time > 5 * 100 * 1000) {
            
            for (auto&& [pl, rep, pos] : ecs::zipper(
                engine.reg.get_components<Player>(), 
                engine.reg.get_components<zef::comp::replicable>(), 
                engine.reg.get_components<zef::comp::position>() 
            )) {
                engine.ServerSend<CommandSetPlayerPos>(rep._id, SETPLAYERPOS, {pos.x, pos.y});
                for (auto&& [pl2, rep2, pos2] : ecs::zipper(
                    engine.reg.get_components<Player>(), 
                    engine.reg.get_components<zef::comp::replicable>(), 
                    engine.reg.get_components<zef::comp::position>() 
                )) {
                    if (rep._id != rep2._id) {
                        engine.ServerSend<CommandSetAllyPos>(rep._id, SETALLYPOS, {rep2._id, pos2.x, pos2.y});
                    }
                }
            }



            pr.time = 0;
        }
    }
}


#endif /* !SYSTEMS_HPP_ */

