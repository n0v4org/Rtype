/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** game
*/

#include <string>

#include "Engine.hpp"
#include "Scenes.hpp"
#include "systems.hpp"

#include "modules/display/systems.hpp"
#include "modules/movement/systems.hpp"
#include "modules/network/systems.hpp"
#include "modules/controller/systems.hpp"
#include "asio.hpp"
#include "CommonCommands.hpp"

void runClient(int sport, int cport, std::string ip) {
  zef::Engine engine;

  engine.initGraphLib("Assets", "");

  engine.GraphLib->saveAnimation("ship", "image", 0, 0, 65, 66);
  engine.GraphLib->saveAnimation("bg", "bg2", 0, 0, 1000, 562);
  engine.GraphLib->saveAnimation("player", "player2", 0, 1, 33 * 3, 17 * 3);
  engine.GraphLib->saveAnimation("bullet", "bullet2", 0, 0, 32, 8);

  //engine.initClient(sport, cport, ip);

  /*engine.registerCommand(SPAWNPLAYER, [](zef::Engine& engine, input_t input) {
      network::game::Commands<CommandSpawnPlayer> csp =
  network::game::Commands<CommandSpawnPlayer>(input);
      engine.instanciatePatron<PlayerPatron>(0.0f, 0.0f,
  csp.getCommand().replicable);
  });

  engine.registerCommand(SPAWNALLY, [](zef::Engine& engine, input_t input) {
      CommandSpawnAlly csp =
  network::game::Commands<CommandSpawnAlly>(input).getCommand();
      engine.instanciatePatron<AllyPatron>(csp.x, csp.y, csp.replicable);
  });

  engine.registerCommand(MOVEALLY, [](zef::Engine& engine, input_t input) {
      CommandMoveAlly mva =
  network::game::Commands<CommandMoveAlly>(input).getCommand();
      //engine.instanciatePatron<AllyPatron>(csp.x, csp.y, csp.replicable);
      for (auto&& [i, rep]:
  ecs::indexed_zipper(engine.reg.get_components<zef::comp::replicable>())) { if
  (rep._id == mva.id) { engine.sendEvent<SetPlayerVectorEvent>(i, mva.x, mva.y);
          }
      }
  });

  engine.registerCommand(SPAWNBULLET, [](zef::Engine& engine, input_t input) {
      CommandSpawnBullet mva =
  network::game::Commands<CommandSpawnBullet>(input).getCommand(); std::cout <<
  "ship to shoot: " << mva.ship << std::endl;

      for (auto&& [i, rep] :
  ecs::indexed_zipper(engine.reg.get_components<zef::comp::replicable>())) { if(
  rep._id == mva.ship) { engine.sendEvent<ShootPlayerEvent>(i);
          }
      }
      //engine.instanciatePatron<AllyPatron>(csp.x, csp.y, csp.replicable);
      //engine.instanciatePatron<BulletPatron>(mva.x, mva.y);
  });

  engine.registerCommand(SETPLAYERPOS, [](zef::Engine& engine, input_t input) {
      CommandSetPlayerPos spp =
  network::game::Commands<CommandSetPlayerPos>(input).getCommand(); for (auto &&
  [pl, pos] : ecs::zipper(engine.reg.get_components<Player>(),
  engine.reg.get_components<zef::comp::position>())) { pos.x = spp.x; pos.y =
  spp.y;
      }
  });

  engine.registerCommand(SETALLYPOS, [](zef::Engine& engine, input_t input) {
      CommandSetAllyPos sap =
  network::game::Commands<CommandSetAllyPos>(input).getCommand(); for (auto &&
  [rep, pos] : ecs::zipper(engine.reg.get_components<zef::comp::replicable>(),
  engine.reg.get_components<zef::comp::position>())) { if (sap.rep == rep._id) {
              pos.x = sap.x;
              pos.y = sap.y;
          }
      }
  });

  engine.registerCommand(ASKPOSITION, [](zef::Engine& engine, input_t input) {
      CommandAskPosition sap =
  network::game::Commands<CommandAskPosition>(input).getCommand();

      for (auto &&[pl, pos] : ecs::zipper(engine.reg.get_components<Player>(),
  engine.reg.get_components<zef::comp::position>())) {
          engine.ClientSend<CommandSendPosition>(SENDPOSITION, {pos.x, pos.y});
      }

  });

  engine.registerCommand(SPAWNMONSTER, [](zef::Engine& engine, input_t input) {
      CommandSpawnMonster spm =
  network::game::Commands<CommandSpawnMonster>(input).getCommand();

      engine.instanciatePatron<EnemyPatron>(spm.x, spm.y, spm.rep);

  });

  engine.registerCommand(KILLMONSTER, [](zef::Engine& engine, input_t input) {
      CommandKillMonster km =
  network::game::Commands<CommandKillMonster>(input).getCommand();

      for (auto&& [i, rep, m] : ecs::indexed_zipper(
          engine.reg.get_components<zef::comp::replicable>(),
          engine.reg.get_components<Monster>()
      )) {
          if (km.rep == rep._id)
          engine.reg.kill_entity(ecs::Entity(i));
      }

  });

  engine.registerCommand(DEATH, [](zef::Engine& engine, input_t input) {
      //Comm km =
  network::game::Commands<CommandKillMonster>(input).getCommand();

      engine.loadScene("lobby");

  });

  engine.registerCommand(DEATHALLY, [](zef::Engine& engine, input_t input) {
      CommandDeatAlly da =
  network::game::Commands<CommandDeatAlly>(input).getCommand();

      for (auto&& [i, rep] :
  ecs::indexed_zipper(engine.reg.get_components<zef::comp::replicable>())) { if
  (rep._id == da.rep) { engine.reg.kill_entity(ecs::Entity(i));
          }
      }

  });*/

  // engine.ClientSend<CommandConnect>(CONNECT, {});

  engine.registerComponent<zef::comp::position>();
  engine.registerComponent<zef::comp::vector>();
  engine.registerComponent<zef::comp::drawable>();
  engine.registerComponent<zef::comp::collidable>();
  engine.registerComponent<Owner>();
  engine.registerComponent<Lifetime>();
  engine.registerComponent<zef::comp::event_listener>();
  engine.registerComponent<zef::comp::controllable>();
  engine.registerComponent<Player>();
  engine.registerComponent<BackGround>();
  engine.registerComponent<zef::comp::replicable>();
  engine.registerComponent<VectorHolder>();
  engine.registerComponent<Monster>();

  // engine.addSystem<>(entitycountdisplay);

  engine.addSystem<>(zef::sys::handle_client);
  engine.addSystem<>(zef::sys::update_user_inputs);
  engine.addSystem<BackGround, zef::comp::position>(handleBackgroundScroll);
  engine.addSystem<Lifetime>(lifetime_system);
  engine.addSystem<VectorHolder, zef::comp::vector>(convertHolderToVect);
  engine.addSystem<zef::comp::vector, Player>(resetPlayerMovement);
  engine.addSystem<zef::comp::controllable>(zef::sys::system_constrollables);
  engine.addSystem<zef::comp::event_listener>(zef::sys::resolveEvent);
  engine.addSystem<zef::comp::vector>(zef::sys::normalize_velocity_vectors);
  engine.addSystem<zef::comp::position, zef::comp::vector>(zef::sys::move);
  engine.addSystem<zef::comp::collidable, zef::comp::position>(
      zef::sys::check_collidables);
  engine.addSystem<zef::comp::event_listener>(zef::sys::resolveEvent);

  engine.addSystem<zef::comp::drawable>(zef::sys::update_animations);
  engine.addSystem<zef::comp::drawable, zef::comp::position>(
      zef::sys::draw_drawables);

  engine.registerScene<LevelScene>("level");
  engine.registerScene<LobbyScene>("lobby");
  engine.loadScene("level");

  engine.run();
}