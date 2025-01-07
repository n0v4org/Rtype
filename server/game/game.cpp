/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** game
*/
#include <vector>
#include <cmath>
#include <iostream>
#include <random>
#include <asio.hpp>

#include "Engine.hpp"
#include "Scenes.hpp"
#include "systems.hpp"

#include "CommonCommands.hpp"

#include "modules/display/systems.hpp"
#include "modules/movement/systems.hpp"
#include "modules/network/systems.hpp"

#include "modules/IModule.hpp"

void runServer(int port) {
  std::cout << __cplusplus << std::endl;

  zef::Engine engine;
  srand(time(NULL));

  engine.initGraphLib("../Assets", "");

  engine.GraphLib->saveAnimation("ship", "image", 0, 0, 65, 66);

  engine.initServer(port);
  /*
      engine.registerCommand(CONNECT, [](zef::Engine& engine, input_t input) {
          engine.ServerSend<CommandSpawnPlayer>(input.id, SPAWNPLAYER,
     {static_cast<size_t>(input.id)});
          engine.instanciatePatron<PlayerPatron>(0.0f, 0.0f, input.id);

          for (auto &i : engine._server->getAllIds()) {
              if (i != input.id) {
                  engine.ServerSend<CommandSpawnAlly>(i, SPAWNALLY, {0.0f, 0.0f,
     static_cast<size_t>(input.id)});
              }
          }

          for (auto &&[pl, pos, rep] :
     ecs::zipper(engine.reg.get_components<Player>(),
     engine.reg.get_components<zef::comp::position>(),
     engine.reg.get_components<zef::comp::replicable>())) { if (rep._id !=
     input.id) engine.ServerSend<CommandSpawnAlly>(input.id, SPAWNALLY, {pos.x,
     pos.y, rep._id});
          }

          for (auto &&[m, rep, pos] :
     ecs::zipper(engine.reg.get_components<Monster>(),
     engine.reg.get_components<zef::comp::replicable>(),
     engine.reg.get_components<zef::comp::position>())) {
              engine.ServerSend<CommandSpawnMonster>(input.id, SPAWNMONSTER,
     {rep._id, pos.x, pos.y});
          }

      });

      engine.registerCommand(MOVEPLAYER, [](zef::Engine& engine, input_t input)
     { CommandMovePlayer cmp =
     network::game::Commands<CommandMovePlayer>(input).getCommand();

          for (auto &&[i,  rep] : ecs::indexed_zipper(
              engine.reg.get_components<zef::comp::replicable>()
              )) {
                  if (rep._id == input.id) {
                      engine.sendEvent<SetPlayerVectorEvent>(i, cmp.x, cmp.y);
                  }
              }

          for (auto &&[p, rep] :
     ecs::zipper(engine.reg.get_components<Player>(),
     engine.reg.get_components<zef::comp::replicable>())) { if (rep._id !=
     input.id) { engine.ServerSend<CommandMoveAlly>(rep._id, MOVEALLY,
     {input.id, cmp.x, cmp.y});
              }
          }
      });

      engine.registerCommand(SHOOTPLAYER, [](zef::Engine& engine, input_t input)
     {

          for (auto &&[i,  rep] : ecs::indexed_zipper(
              engine.reg.get_components<zef::comp::replicable>()
              )) {
                  if (rep._id == input.id) {
                      engine.sendEvent<ShootPlayerEvent>(i);
                  }
              }

          for (auto && [rep, player] : ecs::zipper(
              engine.reg.get_components<zef::comp::replicable>(),
     engine.reg.get_components<Player>()
          )) {
              if (rep._id != input.id) {
                  engine.ServerSend<CommandSpawnBullet>(rep._id, SPAWNBULLET,
     {static_cast<size_t>(input.id)});
              }
          }
      });

      engine.registerCommand(SENDPOSITION, [](zef::Engine& engine, input_t
     input) { CommandSendPosition cmp =
     network::game::Commands<CommandSendPosition>(input).getCommand(); for (auto
     &&[pl, rep, pos] : ecs::zipper(engine.reg.get_components<Player>(),
     engine.reg.get_components<zef::comp::replicable>(),
     engine.reg.get_components<zef::comp::position>())) { if (rep._id ==
     input.id) { pos.x = cmp.x; pos.y = cmp.y;
              }
          }
      });

      */
  engine.registerComponent<zef::comp::position>();
  engine.registerComponent<zef::comp::vector>();
  engine.registerComponent<zef::comp::drawable>();
  engine.registerComponent<zef::comp::collidable>();
  engine.registerComponent<Health>();
  engine.registerComponent<Owner>();
  engine.registerComponent<Lifetime>();
  engine.registerComponent<zef::comp::event_listener>();
  engine.registerComponent<zef::comp::replicable>();
  engine.registerComponent<VectorHolder>();
  engine.registerComponent<Player>();
  engine.registerComponent<PlayerReplacer>();
  engine.registerComponent<Monster>();

  engine.reg.spawn_entity();
  engine.loadModules();

  engine.reg.disp();
  ////engine.addSystem<>(entitycountdisplay);

  // engine.addSystem<Lifetime>(lifetime_system);
  // engine.addSystem<>(zef::sys::handle_server);

  // engine.addSystem<VectorHolder, zef::comp::vector>(convertHolderToVect);
  // engine.addSystem<zef::comp::vector>(zef::sys::normalize_velocity_vectors);
  // engine.addSystem<zef::comp::position, zef::comp::vector>(zef::sys::move);
  // engine.addSystem<PlayerReplacer>(syncPlayers);

  // engine.addSystem<Player, zef::comp::replicable>(spawnEnemies);

  engine.addSystem<zef::comp::collidable, zef::comp::position>("zefir",
      zef::sys::check_collidables);
  // engine.addSystem<zef::comp::event_listener>(zef::sys::resolveEvent);

  // engine.addSystem<Health>(handleHealth);

  engine.addSystem<zef::comp::drawable>("zefir", zef::sys::update_animations);
  engine.addSystem<zef::comp::drawable, zef::comp::position>(
      "zefir", zef::sys::draw_drawables);

    engine.addSystem<zef::comp::position>("zefir", [](zef::Engine &engine, ecs::sparse_array<zef::comp::position> &pos){
        for (auto &&[p] : ecs::zipper(pos)) {
            std::cout << "x: " << p.x << " y: " << p.y << std::endl;
        }
    });

    engine.addEntityComponent<zef::comp::position>(engine.reg.spawn_entity(), 2.0f, 9.0f);

  engine.loadPatron("../Assets/config/patronPlayer.json");
  engine.instanciatePatron("Player", 3, 4.5f, 56.90f);

  engine.registerScene<LevelScene>("level");
  engine.registerScene<LobbyScene>("lobby");
  // engine.loadScene("level");

  engine.run();
}
