/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** game
*/

#include <string>
#include <cstring>
#include <chrono>
#include <iostream>

#include "Engine.hpp"
#include "Scenes.hpp"
#include "systems.hpp"

#include "modules/display/systems.hpp"
#include "modules/movement/systems.hpp"
#include "modules/network/systems.hpp"
#include "modules/controller/systems.hpp"
#include "modules/textzone/systems.hpp"
#include "events.hpp"
#include "asio.hpp"
#include "CommonCommands.hpp"
#include "UdpProtoCommands.hpp"

#include <random>
int generateRandomPort() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1024, 65535);

    return distr(gen);
  }


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
  engine.GraphLib->saveAnimation("enemyCrab", "enemyCrab", 4 * 33, 1, 33, 34);

  engine.GraphLib->saveAnimation("enemyRobot", "enemyRobot", 1 * 56, 0, 56, 59);
  engine.GraphLib->saveAnimation("robotBulletA", "robotBulletA", 0, 0, 65, 17);
  engine.GraphLib->saveAnimation("enemyRobotS", "enemyRobot", 2 * 56, 0, 56,
                                 59);

  engine.GraphLib->saveAnimation("AWall", "AWall", 0, 0, 48, 40);
  engine.GraphLib->saveAnimation("BWall", "BWall", 0, 0, 48, 8);
  engine.GraphLib->saveAnimation("CWall", "CWall", 0, 0, 189, 72);

  engine.GraphLib->saveAnimation("BossOne", "BossOne", 0, 0, 162, 212);
  engine.GraphLib->saveAnimation("BossOneMini", "BossOneMini", 0, 0, 33, 37);
  engine.GraphLib->saveAnimation("miniBossBullet", "miniBossBullet", 0, 0, 23,
                                 23);
  engine.GraphLib->saveAnimation("EBullet", "EBullet", 0, 0, 18, 18);

  //engine.registerCommandTcp("221", [ip](zef::Engine& engine, input_t input) {
  //  std::vector <size_t> idAlly;
  //  nlohmann::json rep = nlohmann::json::parse(input.tcp_payload);
  //  for (auto &i : rep["players"])
  //      idAlly.push_back(i[1]);
  //  engine.newLoadScene<LevelScene>(idAlly);
  //});
//
  engine.registerCommandTcp("207", [ip](zef::Engine& engine, input_t input) {
      std::cout << input.tcp_payload << std::endl;
        nlohmann::json rep = nlohmann::json::parse(input.tcp_payload);
      std::cout << "switching port into " << rep["tcp_port"] << " " << rep["udp_port"] << " " << rep["player_uuid"]  << std::endl;
      engine._client->reset_clients(rep["udp_port"], generateRandomPort(), rep["tcp_port"], ip);
      std::this_thread::sleep_for(std::chrono::microseconds(100));
      std::string uuid = rep["player_uuid"];
      std::string loginstr = "LOGIN " + uuid;
      std::cout << "sending " << uuid << " " << loginstr << std::endl;
      engine.ClientSendTcp(loginstr);
        login_t lgt;
      strncpy(lgt.pwd, uuid.c_str(), 21);
      engine.ClientSendUdp<login_t>(LOGIN, lgt);
  });


  engine.registerCommand(SEND_POS, [](zef::Engine& engine, input_t input) {
    sssend_pos_t sp = network::game::Commands<sssend_pos_t>(input).getCommand();
    for (auto &&[i, rep, ship, pos]: ecs::indexed_zipper(
        engine.reg.get_components<zef::comp::replicable>(),
        engine.reg.get_components<Ship>(),
        engine.reg.get_components<zef::comp::position>()
    )) {
        if (rep._id == sp.rep) {
            pos.x = sp.x;
            pos.y = sp.y;
        }
    }
  });

  engine.registerCommand(SHOOT_ALLY, [](zef::Engine& engine, input_t input) {
    shoot_ally_t sa = network::game::Commands<shoot_ally_t>(input).getCommand();
    std::cout << "shoot" << sa.rep;
        for (auto &&[i, rep, ship]: ecs::indexed_zipper(
            engine.reg.get_components<zef::comp::replicable>(),
            engine.reg.get_components<Ship>())) {
                if (rep._id == sa.rep) {
                    engine.sendEvent<ShootPlayerEvent>(i, sa.size);
                }
            }
  });

   engine.registerCommand(UPDATE_HP, [](zef::Engine& engine, input_t input) {
    update_hp_t uh = network::game::Commands<update_hp_t>(input).getCommand();
    std::cout << "set self damage" << "\n";
    for (auto &&[i, p, h]: ecs::indexed_zipper(engine.reg.get_components<Player>(), engine.reg.get_components<Health>()))
    h._hp = uh.hp;
  });

  engine.registerCommand(ALLY_UPDATE_HP, [](zef::Engine& engine, input_t input) {
    ally_update_hp_t uah = network::game::Commands<ally_update_hp_t>(input).getCommand();
    std::cout << "set ally damage" << uah.hp << uah.rep << "\n";
    for (auto &&[i, s, r, h]: ecs::indexed_zipper(engine.reg.get_components<Ship>(), engine.reg.get_components<zef::comp::replicable>(), engine.reg.get_components<Health>()))
    if (r._id == uah.rep)
    h._hp = uah.hp;
  });

  engine.registerCommand(KILL, [](zef::Engine& engine, input_t input) {
    kill_t uh = network::game::Commands<kill_t>(input).getCommand();
    std::cout << "selfkill" << "\n";
    for (auto &&[i, p, h]: ecs::indexed_zipper(engine.reg.get_components<Player>(), engine.reg.get_components<Health>()))
    engine.sendEvent<OnDeath>(i);
  });

  engine.registerCommand(KILL_ALLY, [](zef::Engine& engine, input_t input) {
    kill_ally_t ka = network::game::Commands<kill_ally_t>(input).getCommand();
    std::cout << "killally"  << ka.rep << "\n";
    for (auto &&[i, s, r, h]: ecs::indexed_zipper(engine.reg.get_components<Ship>(), engine.reg.get_components<zef::comp::replicable>(), engine.reg.get_components<Health>()))
    if (r._id == ka.rep)
    engine.sendEvent<OnDeath>(i);
  });

  engine.registerCommand(SPAWN_PLANE, [](zef::Engine& engine, input_t input) {
    spawn_plane_t sp = network::game::Commands<spawn_plane_t>(input).getCommand();
    std::cout << "spawnplane"  << sp.rep << "\n";
    engine.instanciatePatron<EnemyPlanePatron>(sp.x, sp.y, sp.rep);

  });

  engine.registerCommand(SPAWN_CRAB, [](zef::Engine& engine, input_t input) {
    spawn_crab_t sp = network::game::Commands<spawn_crab_t>(input).getCommand();
    std::cout << "spawncrab"  << sp.rep << "\n";
    engine.instanciatePatron<EnemyCrabPatron>(sp.x, sp.y, sp.rep);
  });
  engine.registerCommand(SPAWN_ROBOT, [](zef::Engine& engine, input_t input) {
    spawn_robot_t sp = network::game::Commands<spawn_robot_t>(input).getCommand();
    std::cout << "spawnrobot"  << sp.rep << "\n";
    engine.instanciatePatron<EnemyRobotPatron>(sp.x, sp.y, sp.rep);
  });
  engine.registerCommand(SPAWN_BOSS, [](zef::Engine& engine, input_t input) {
    spawn_boss_t sp = network::game::Commands<spawn_boss_t>(input).getCommand();
    std::cout << "spawnboss"  << sp.rep << "\n";
    const ecs::Entity& b = engine.instanciatePatron<BossOnePatron>(sp.x, sp.y, sp.rep);
  });

  engine.registerCommand(PLANE_SHOOT, [](zef::Engine& engine, input_t input) {
    plane_shoot_t sp = network::game::Commands<plane_shoot_t>(input).getCommand();
    std::cout << "shootplane"  << sp.rep << "\n";
    for (auto &&[i, m, r] : ecs::indexed_zipper(engine.reg.get_components<Monster>(), engine.reg.get_components<zef::comp::replicable>())) {
        if (r._id == sp.rep)
            engine.sendEvent<PlaneShootEvent>(i, sp.vx, sp.vy);
    }
  });

  engine.registerCommand(CRAB_NEW_DIR, [](zef::Engine& engine, input_t input) {
    crab_new_dir_t sp = network::game::Commands<crab_new_dir_t>(input).getCommand();
    std::cout << "crabnewdir"  << sp.rep << "\n";
    for (auto &&[i, m, r, v, p] : ecs::indexed_zipper(engine.reg.get_components<Monster>(), engine.reg.get_components<zef::comp::replicable>(), engine.reg.get_components<zef::comp::vector>(), engine.reg.get_components<zef::comp::position>())) {
        if (r._id == sp.rep) {
            v.x = sp.vx;
            v.y = sp.vy;
            p.x = sp.x;
            p.y = sp.y;
        }
    }
  });

  engine.registerCommand(ROBOT_NEW_DIR, [](zef::Engine& engine, input_t input) {
    robot_new_dir_t sp = network::game::Commands<robot_new_dir_t>(input).getCommand();
    std::cout << "robondir"  << sp.rep << "\n";
    for (auto &&[i, m, r, v, p] : ecs::indexed_zipper(engine.reg.get_components<Monster>(), engine.reg.get_components<zef::comp::replicable>(), engine.reg.get_components<zef::comp::vector>(), engine.reg.get_components<zef::comp::position>())) {
        if (r._id == sp.rep) {
            v.x = sp.vx;
            v.y = sp.vy;
            p.x = sp.x;
            p.y = sp.y;
        }
    }
  });

  engine.registerCommand(ROBOT_SHOOT, [](zef::Engine& engine, input_t input) {
    robot_shoot_t sp = network::game::Commands<robot_shoot_t>(input).getCommand();
    std::cout << "robontir"  << sp.rep << "\n";
    for (auto &&[i, m, r, p] : ecs::indexed_zipper(engine.reg.get_components<Monster>(), engine.reg.get_components<zef::comp::replicable>(), engine.reg.get_components<zef::comp::position>())) {
        if (r._id == sp.rep) {
            float tmpx = p.x;
            float tmpy = p.y;
            p.x = sp.x;
            p.y = sp.y;
            engine.sendEvent<RobotShoot>(i);
            p.x = tmpx;
            p.y = tmpy;

        }
    }
  });

  engine.registerCommand(BOSS_SHOOT, [](zef::Engine& engine, input_t input) {
    boss_shoot_t sp = network::game::Commands<boss_shoot_t>(input).getCommand();
    std::cout << "bosshoot"  << sp.rep << "\n";
    for (auto &&[i, m, r] : ecs::indexed_zipper(engine.reg.get_components<Monster>(), engine.reg.get_components<zef::comp::replicable>())) {
        if (r._id == sp.rep) {
            engine.sendEvent<MiniBossShoot>(i);
        }
    }
  });

   engine.registerCommand(KILL_MONSTER, [](zef::Engine& engine, input_t input) {
    kill_monster_t sp = network::game::Commands<kill_monster_t>(input).getCommand();
    std::cout << "killmonster"  << sp.rep << "\n";
    for (auto &&[i, m, r] : ecs::indexed_zipper(engine.reg.get_components<Monster>(), engine.reg.get_components<zef::comp::replicable>())) {
        if (r._id == sp.rep) {
            engine.sendEvent<OnDeath>(i);
        }
    }
  });

   engine.initClient(sport, generateRandomPort(), cport, ip);
   sleep(1);

//   engine.ClientSendTcp("JOIN 1 magicarpe");
//   sleep(1);
//   engine.ClientSendTcp("SET_PLAYER_READY");


  // std::this_thread::sleep_for(std::chrono::microseconds(100));

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
  engine.registerComponent<zef::comp::drawableText>();
  engine.registerComponent<zef::comp::collidable>();
  engine.registerComponent<Owner>();
  engine.registerComponent<Health>();
  engine.registerComponent<Lifetime>();
  engine.registerComponent<zef::comp::event_listener>();
  engine.registerComponent<zef::comp::controllable>();
  engine.registerComponent<Player>();
  engine.registerComponent<BackGround>();
  engine.registerComponent<SounbdBar>();
  engine.registerComponent<zef::comp::replicable>();
  engine.registerComponent<VectorHolder>();
  engine.registerComponent<Monster>();
  engine.registerComponent<Laser>();
  engine.registerComponent<Ship>();
  engine.registerComponent<TurretTurnRate>();
  engine.registerComponent<Damaged>();
  engine.registerComponent<SinusoidalMotion>();
  engine.registerComponent<MoveCamera>();
  engine.registerComponent<SinusoidalAboveMotion>();
  engine.registerComponent<zef::comp::clickable>();
  engine.registerComponent<Tab>();
  engine.registerComponent<PlayerSlot>();
  engine.registerComponent<PlayerKickAdminWindow>();
  engine.registerComponent<SlotRedo>();
  engine.registerComponent<zef::comp::LobbyOffset>();
  engine.registerComponent<zef::comp::LobbyCreateTrack>();
  engine.registerComponent<zef::comp::LobbyInfoTrack>();
  engine.registerComponent<zef::comp::MyInfo>();
  engine.registerComponent<zef::comp::textZone>();
  engine.registerComponent<PwdZone>();
  engine.registerComponent<NameZone>();
  engine.registerComponent<MsgZone>();
  engine.registerComponent<UsrZone>();
  engine.registerComponent<ChatMsgTrack>();
  engine.registerComponent<MsgDel>();


  engine.registerComponent<zef::comp::gravity>();
  engine.registerComponent<zef::comp::rigidbody>();
  engine.registerComponent<zef::comp::name>();
    //engine.loadModules();

  //   // engine.addSystem<>(entitycountdisplay);

  //engine.addSystem<Tab>("zefir", [](zef::Engine& engine, ecs::sparse_array<Tab>& mvs){
  //  for (auto &&[i, mv] : ecs::indexed_zipper(mvs)) {
  //    std::cout << i;
  //  } std::cout << "\n";
  //});

  engine.addSystem<>("zefir", zef::sys::update_user_inputs);
  engine.addSystem<MoveCamera>(
      "zefir", [](zef::Engine& engine, ecs::sparse_array<MoveCamera>& mvs) {
        for (auto&& [i, mv] : ecs::indexed_zipper(mvs))
            engine.GraphLib->moveCamera(2, 0, 1);
      });
    engine.addSystem<Monster>(
      "zefir", [](zef::Engine& engine, ecs::sparse_array<Monster>& mvs) {
        for (auto&& [i, mv] : ecs::indexed_zipper(mvs)) {
            std::cout << "x: " << engine.fetchEntityComponent<zef::comp::position>(i).x << std::endl;
            std::cout << "y: " << engine.fetchEntityComponent<zef::comp::position>(i).y << std::endl;

        }
            //std::cout << engine.fetchEntityComponent<zef::comp::position>(i).y << std::endl;
      });

    engine.addSystem<Player, zef::comp::position, MoveCamera>("zefir", [](zef::Engine& engine, ecs::sparse_array<Player>& pls, ecs::sparse_array<zef::comp::position>& poss, ecs::sparse_array<MoveCamera>& mvs){
        for (auto &&[i, p, pos] : ecs::indexed_zipper(pls, poss)) {
            if (pos.x >= 2000)
                for (auto &&[j, m] : ecs::indexed_zipper(mvs)) {
                    engine.reg.kill_entity(ecs::Entity(j));
                }
        }
    });

  engine.addSystem<zef::comp::clickable, zef::comp::position>("zefir", zef::sys::handleclickable);
  engine.addSystem<zef::comp::event_listener>("zefir",
                                              zef::sys::resolveEvent
                                              );

  engine.addSystem<>("zefir", zef::sys::handle_client);

  engine.addSystem<Lifetime>("zefir", lifetime_system);
  engine.addSystem<zef::comp::vector, Player>("zefir", resetPlayerMovement);
  engine.addSystem<zef::comp::controllable>("zefir",
                                            zef::sys::system_constrollables);

    //engine.addSystem<zef::comp::vector, zef::comp::position, zef::comp::gravity>("zefir", zef::sys::apply_gravity);

  engine.addSystem<zef::comp::event_listener>("zefir", zef::sys::resolveEvent);
  // engine.addSystem<zef::comp::vector>("zefir",
  //                                     zef::sys::normalize_velocity_vectors);
  engine.addSystem<Ship, zef::comp::vector, zef::comp::drawable>("zefir",
                                                                 animateShips);
  engine.addSystem<zef::comp::position, zef::comp::vector>("zefir",
                                                           zef::sys::move);
  engine.addSystem<Ship, zef::comp::position, MoveCamera>("zefir", autoWalkShips);
  engine.addSystem<zef::comp::collidable, zef::comp::position>(
      "zefir", zef::sys::check_collidables);
  engine.addSystem<zef::comp::event_listener>("zefir", zef::sys::resolveEvent);

  engine.addSystem<Damaged, zef::comp::drawable>("zefir", handleDamageEffect);
  engine.addSystem<zef::comp::drawable>("zefir", zef::sys::update_animations);
  engine.addSystem<zef::comp::drawable, zef::comp::position>(
      "zefir", zef::sys::draw_drawables);
  engine.addSystem<zef::comp::drawableText, zef::comp::position>(
      "zefir", zef::sys::draw_texts);
  engine.addSystem<zef::comp::textZone, zef::comp::position>(
      "zefir", zef::sys::UpdateTextInputs);
  engine.addSystem<zef::comp::textZone, zef::comp::position>(
      "zefir", zef::sys::DrawTextInputs);
  engine.addSystem<SounbdBar, zef::comp::position>("zefir",drawSoundBar);
  engine.addSystem<Ship, Health, zef::comp::position>("zefir", drawHpBarPlayer);
  engine.addSystem<Player, Laser, zef::comp::position>("zefir", drawLoadBar);
  engine.addSystem<SinusoidalMotion, zef::comp::vector>("zefir",
                                                        sinusoidalVectorSystem);
  engine.addSystem<SinusoidalAboveMotion, zef::comp::position>(
      "zefir", sinusoidalAbovePositionSystem);



  engine.addSystem<zef::comp::position, Player>(
    "zefir",
    send_player_position
);
  
  engine.addSystem<zef::comp::collidable, zef::comp::position>(
      "zefir", zef::sys::check_collidables);
  engine.addSystem<zef::comp::rigidbody, zef::comp::position, zef::comp::vector>("zefir", zef::sys::check_rigidity);

  // engine.registerScene<LevelScene>("level");
  // engine.registerScene<LobbyScene>("lobby");
  // engine.loadScene("level");

  engine.newLoadScene<MenuScene>();
//  engine.newLoadScene<TestScene>();

    engine.run();
}