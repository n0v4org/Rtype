/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** game
*/

#include <string>
#include <cstring>
#include <chrono>

#include "Engine.hpp"
#include "Scenes.hpp"
#include "systems.hpp"

#include "modules/display/systems.hpp"
#include "modules/movement/systems.hpp"
#include "modules/network/systems.hpp"
#include "modules/controller/systems.hpp"
#include "asio.hpp"
#include "CommonCommands.hpp"
#include "UdpProtoCommands.hpp"

void runClient(int sport, int cport, std::string ip) {
  zef::Engine engine;

  engine.initGraphLib("../Assets", "");

  engine.GraphLib->saveAnimation("ship", "image", 0, 0, 65, 66);

  engine.GraphLib->saveAnimation("bg", "bg2", 0, 0, 1000, 562);

  engine.GraphLib->saveAnimation("player_t2", "player2", 0, 1, 33 * 3, 17 * 3);
  engine.GraphLib->saveAnimation("player_t1", "player2", 33 * 3, 1, 33 * 3,
                                 17 * 3);
  engine.GraphLib->saveAnimation("player_0", "player2", 33 * 3 * 2, 1, 33 * 3,
                                 17 * 3);
  engine.GraphLib->saveAnimation("player_d1", "player2", 33 * 3 * 3, 1, 33 * 3,
                                 17 * 3);
  engine.GraphLib->saveAnimation("player_d2", "player2", 33 * 3 * 4, 1, 33 * 3,
                                 17 * 3);

  engine.GraphLib->saveAnimation("bullet", "allyBullet", 0, 0, 32, 8);
  engine.GraphLib->saveAnimation("bullet2", "allyBullet2", 0, 0, 48, 14);

  engine.GraphLib->saveAnimation("fireball", "fireball", 0, 0, 8, 8);

  engine.GraphLib->saveAnimation("blast", "blast", 0, 0, 33, 32);


  engine.GraphLib->saveAnimation("turretu", "turret", 0, 0, 17, 18);
  engine.GraphLib->saveAnimation("turretd", "turret", 0, 1, 17, 18);

  engine.GraphLib->saveAnimation("enemyPlaneG", "enemyPlaneG", 0, 0, 33, 35);
  engine.GraphLib->saveAnimation("enemyCrab", "enemyCrab", 4*33, 1, 33, 34);

  engine.GraphLib->saveAnimation("enemyRobot", "enemyRobot", 1*56, 0, 56, 59);
  engine.GraphLib->saveAnimation("robotBulletA", "robotBulletA", 0, 0, 65, 17);
  engine.GraphLib->saveAnimation("enemyRobotS", "enemyRobot", 2*56, 0, 56, 59);

  engine.GraphLib->saveAnimation("AWall", "AWall", 0, 0, 48, 40);
  engine.GraphLib->saveAnimation("BWall", "BWall", 0, 0, 48, 8);
  engine.GraphLib->saveAnimation("CWall", "CWall", 0, 0, 189, 72);



  engine.registerCommandTcp("202", [](zef::Engine& engine, input_t input) {
      std::cout << input.tcp_payload << std::endl;
  });
  engine.registerCommandTcp("208", [](zef::Engine& engine, input_t input) {
      std::cout << input.tcp_payload << std::endl;
  });
  engine.registerCommandTcp("203", [](zef::Engine& engine, input_t input) {
      std::cout << input.tcp_payload << std::endl;
  });
  engine.registerCommandTcp("204", [ip](zef::Engine& engine, input_t input) {
      std::cout << input.tcp_payload << std::endl;
        nlohmann::json rep = nlohmann::json::parse(input.tcp_payload);
      std::cout << "switching port into " << rep["tcp_port"] << " " << rep["udp_port"] << " " << rep["player_uuid"]  << std::endl;
      engine._client->reset_clients(rep["udp_port"], 15005, rep["tcp_port"], ip);
      std::this_thread::sleep_for(std::chrono::microseconds(100));
      std::string uuid = rep["player_uuid"];
      std::string loginstr = "LOGIN " + uuid;
      std::cout << "sending " << uuid << " " << loginstr << std::endl;
      engine.ClientSendTcp(loginstr);
        login_t lgt;
      strncpy(lgt.pwd, uuid.c_str(), 21);
      std::cout << "hohoho\n";
      engine.ClientSendUdp<login_t>(LOGIN, lgt);
      std::cout << "hiih\n";
  });

  

engine.initClient(sport, cport, 14001, ip);
std::this_thread::sleep_for(std::chrono::microseconds(100));
engine.ClientSendTcp("JOIN 1 magicarpe");
std::this_thread::sleep_for(std::chrono::microseconds(100));

engine.ClientSendTcp("SET_PLAYER_READY");
engine.ClientSendTcp("LAUNCH_GAME");
  /*engine.registerCommand(SPAWNALLY, [](zef::Engine& engine, input_t input) {
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
  engine.registerComponent<Health>();
  engine.registerComponent<Lifetime>();
  engine.registerComponent<zef::comp::event_listener>();
  engine.registerComponent<zef::comp::controllable>();
  engine.registerComponent<Player>();
  engine.registerComponent<BackGround>();
  engine.registerComponent<zef::comp::replicable>();
  engine.registerComponent<VectorHolder>();
  engine.registerComponent<Monster>();
  engine.registerComponent<Laser>();
  engine.registerComponent<Ship>();
  engine.registerComponent<TurretTurnRate>();
  engine.registerComponent<Damaged>();
  engine.registerComponent<SinusoidalMotion>();
  engine.registerComponent<zef::comp::gravity>();
  engine.registerComponent<zef::comp::rigidbody>();
  engine.registerComponent<zef::comp::name>();
    //engine.loadModules();
    
  //   // engine.addSystem<>(entitycountdisplay);

  engine.addSystem<>("zefir", zef::sys::update_user_inputs);
  engine.addSystem<>("zefir", [](zef::Engine& engine) {
    engine.GraphLib->moveCamera(2, 0, 1);
  });

  //engine.addSystem<>("zefir", zef::sys::handle_client);

  engine.addSystem<BackGround, zef::comp::position>("zefir",
                                                    handleBackgroundScroll);
  engine.addSystem<Lifetime>("zefir", lifetime_system);
  engine.addSystem<zef::comp::vector, Player>("zefir", resetPlayerMovement);
  engine.addSystem<zef::comp::controllable>("zefir",
                                            zef::sys::system_constrollables);

    engine.addSystem<zef::comp::vector, zef::comp::position, zef::comp::gravity>("zefir", zef::sys::apply_gravity);

  engine.addSystem<zef::comp::event_listener>("zefir", zef::sys::resolveEvent);
  engine.addSystem<zef::comp::vector>("zefir",
                                      zef::sys::normalize_velocity_vectors);
  engine.addSystem<Ship, zef::comp::vector, zef::comp::drawable>("zefir",
                                                                 animateShips);
  engine.addSystem<zef::comp::position, zef::comp::vector>("zefir",
                                                           zef::sys::move);
  
  engine.addSystem<zef::comp::event_listener>("zefir", zef::sys::resolveEvent);

  engine.addSystem<Damaged, zef::comp::drawable>("zefir", handleDamageEffect);
  engine.addSystem<zef::comp::drawable>("zefir", zef::sys::update_animations);
  engine.addSystem<zef::comp::drawable, zef::comp::position>(
      "zefir", zef::sys::draw_drawables);
  engine.addSystem<Ship, Health, zef::comp::position>("zefir", drawHpBarPlayer);
  engine.addSystem<Player, Laser, zef::comp::position>("zefir", drawLoadBar);
  engine.addSystem<SinusoidalMotion, zef::comp::vector>(
      "zefir",
      sinusoidalVectorSystem
  );
  
  engine.addSystem<zef::comp::collidable, zef::comp::position>(
      "zefir", zef::sys::check_collidables);
  engine.addSystem<zef::comp::rigidbody, zef::comp::position, zef::comp::vector>("zefir", zef::sys::check_rigidity);
  engine.addSystem<Ship, zef::comp::vector>("zefir", autoWalkShips);

  //engine.registerScene<LevelScene>("level");
  //engine.registerScene<LobbyScene>("lobby");
  //engine.loadScene("level");

  engine.newLoadScene<LevelScene>();

  engine.run();
}