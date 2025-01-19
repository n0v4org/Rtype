/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** systems
*/

#ifndef SYSTEMS_HPP_
#define SYSTEMS_HPP_

#include <stdlib.h>
#include <iostream>

#include "components.hpp"
#include "Engine.hpp"
#include "CommonCommands.hpp"
#include "modules/network/components.hpp"

inline void entitycountdisplay(zef::Engine& engine) {
  std::cout << engine.reg.getEntityCount() << std::endl;
}

inline void lifetime_system(zef::Engine& engine,
                            ecs::sparse_array<Lifetime>& lts) {
  for (auto&& [i, lt] : ecs::indexed_zipper(lts)) {
    lt.microsecs -= engine.elapsed.count();
    if (lt.microsecs <= 0)
      engine.reg.kill_entity(ecs::Entity(i));
  }
}

inline void handleHealth(zef::Engine& engine, ecs::sparse_array<Health>& hps) {
  for (auto&& [i, hp] : ecs::indexed_zipper(hps)) {
    if (hp.hp <= 0) {
      try {
        engine.fetchEntityComponent<Monster>(i);

        zef::comp::replicable& r =
            engine.fetchEntityComponent<zef::comp::replicable>(i);
        for (auto&& [pl, rep] :
             ecs::zipper(engine.reg.get_components<Player>(),
                         engine.reg.get_components<zef::comp::replicable>())) {
          // engine.ServerSend<CommandKillMonster>(rep._id, KILLMONSTER,
          // {r._id});
        }
      } catch (const std::exception& e) {
      }
      try {
        engine.fetchEntityComponent<Player>(i);

        zef::comp::replicable& r =
            engine.fetchEntityComponent<zef::comp::replicable>(i);
        // engine.ServerSend<CommandDeath>(r._id, DEATH, {});
        for (auto&& [pl, rep] :
             ecs::zipper(engine.reg.get_components<Player>(),
                         engine.reg.get_components<zef::comp::replicable>())) {
          // engine.ServerSend<CommandDeatAlly>(rep._id, DEATHALLY, {r._id});
        }
      } catch (const std::exception& e) {
      }
      engine.reg.kill_entity(ecs::Entity(i));
    }
  }
}

// inline void spawnEnemies(
//     zef::Engine& engine, ecs::sparse_array<Player>& players,
//     ecs::sparse_array<zef::comp::replicable>& replicables) {
//   unsigned int seed = time(NULL);
//   if (engine._enemyCooldown > 7 * 1000 * 1000) {
//     for (int i = 0; i < 5; ++i) {
//       float y = 800 - 400;
//       float x = 900 + 150;
//       engine.instanciatePatron<EnemyPatron>(x, y, engine.replicableId);
//       std::cout << "rep: " << engine.replicableId << std::endl;
//       for (auto&& [player, rep] : ecs::zipper(players, replicables)) {
//         // engine.ServerSend<CommandSpawnMonster>(rep._id, SPAWNMONSTER,
//         //{engine.replicableId, x, y});
//       }
//       engine.replicableId++;
//     }
//     engine._enemyCooldown = 0;
//   }
//   engine._enemyCooldown += engine.elapsed.count();
// }

inline void convertHolderToVect(zef::Engine& engine,
                                ecs::sparse_array<VectorHolder>& vhs,
                                ecs::sparse_array<zef::comp::vector>& vvs) {
  for (auto&& [i, vh, vc] : ecs::indexed_zipper(vhs, vvs)) {
    vc.x = vh.x;
    vc.y = vh.y;
  }
}

inline void syncPlayers(zef::Engine& engine,
                        ecs::sparse_array<PlayerReplacer>& prs) {
  for (auto&& [pr] : ecs::zipper(prs)) {
    pr.time += engine.elapsed.count();

    if (pr.time > 2 * 100 * 1000) {
      for (auto&& [pl, rep, pos] :
           ecs::zipper(engine.reg.get_components<Player>(),
                       engine.reg.get_components<zef::comp::replicable>(),
                       engine.reg.get_components<zef::comp::position>())) {
        // engine.ServerSend<CommandAskPosition>(rep._id, ASKPOSITION, {});

        for (auto&& [pl2, rep2, pos2] :
             ecs::zipper(engine.reg.get_components<Player>(),
                         engine.reg.get_components<zef::comp::replicable>(),
                         engine.reg.get_components<zef::comp::position>())) {
          if (rep._id != rep2._id) {
            // engine.ServerSend<CommandSetAllyPos>(rep._id, SETALLYPOS,
            //{rep2._id, pos2.x, pos2.y});
          }
        }
      }

      pr.time = 0;
    }
  }
}

inline void sinusoidalVectorSystem(zef::Engine& engine,
                            ecs::sparse_array<SinusoidalMotion>& sms,
                            ecs::sparse_array<zef::comp::vector>& vecs) {
  for (auto&& [i, sm, vec] : ecs::indexed_zipper(sms, vecs)) {
    float dt = engine.elapsed.count() / 1'000'000.f;

    sm.phase += sm.frequency * dt;

    vec.x = sm.speedX;
    vec.y = sm.amplitude * std::sin(sm.phase);
  }
}

inline void sinusoidalAbovePositionSystem(
    zef::Engine& engine, ecs::sparse_array<SinusoidalAboveMotion>& sams,
    ecs::sparse_array<zef::comp::position>& poss) {
  for (auto&& [i, sam, pos] : ecs::indexed_zipper(sams, poss)) {
    float dt = engine.elapsed.count() / 1'000'000.f;
    sam.phase += sam.frequency * dt;
    float wave = (std::sin(sam.phase) + 1.f) * 0.5f;
    pos.y      = sam.baseY - wave * sam.amplitude;
  }
}

inline void showShipPos(zef::Engine& e, ecs::sparse_array<Ship>& sss,ecs::sparse_array<zef::comp::position>& pss) {
    for (auto &&[i, ss, pos] : ecs::indexed_zipper(sss, pss)) {
      std::cout << "theo bibou" << pos.x << " " << pos.y << "\n";
    } 
}

#endif /* !SYSTEMS_HPP_ */
