/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** game
*/

#include <string>
#include <iostream>
#include "UdpProtoCommands.hpp"

#include "EnemyCrabPatron.hpp"
#include "EnemyPlanePatron.hpp"
#include "EnemyRobotPatron.hpp"

#include "BossOnePatron.hpp"

#include "Game.hpp"

namespace rtype {

  Game::Game() {
  }

  void Game::RegisterGameCmd() {

    
  }

  void Game::launch_game(std::vector<std::string> player_uuid, int tcp_port,
              int udp_port) {

    std::cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" << std::endl;
    _engine.registerCommand(SHOOT, [this](zef::Engine& engine, input_t input)  {
      shoot_t sh = network::game::Commands<shoot_t>(input).getCommand();
      size_t realId = -1;
      for (int i = 0; i < this->_players.size(); i++) if (this->_players[i].udp_id == input.id) realId = i;
      for (auto &&[i, r, ship, pos] : ecs::indexed_zipper(
        engine.reg.get_components<zef::comp::replicable>(),
        engine.reg.get_components<Ship>(),
        engine.reg.get_components<zef::comp::position>()
      )) {
        if (r._id == realId) {
          engine.instanciatePatron<BulletPatron>(pos.x, pos.y, sh.size);
        }
        if (r._id != realId) {
          std::cout << "sending" << realId << " to: " << r._id << std::endl;
          engine.ServerSendUdp<shoot_ally_t>(this->_players[r._id].tcp_id, SHOOT_ALLY, {sh.size, realId});
        }
      }
    });

    _engine.registerCommand(GET_POS, [this](zef::Engine& engine, input_t input) {
      pos_t post = network::game::Commands<pos_t>(input).getCommand();
      size_t realId = -1;
      for (int i = 0; i < this->_players.size(); i++) if (this->_players[i].udp_id == input.id) realId = i;
      for (auto &&[i, r, pos, ship] : ecs::indexed_zipper(
        engine.reg.get_components<zef::comp::replicable>(),
        engine.reg.get_components<zef::comp::position>(),
        engine.reg.get_components<Ship>()
      )) {
        if (r._id == realId) {
          pos.x = post.x;
          pos.y = post.y;
        }
        if (r._id != realId) {
          engine.ServerSendUdp<sssend_pos_t>(this->_players[r._id].tcp_id, SEND_POS, {post.x, post.y, realId});
        }
      }
    });

    _engine.registerCommand(TEST, [this](zef::Engine& engine, input_t input) {
      test_t post = network::game::Commands<test_t>(input).getCommand();
      std::cout << "-----[DEBUG]-----\n";
      std::cout << "do a thing" << std::endl;
      std::cout << "count: " <<engine.reg._entityCount << std::endl;
      std::cout << "sendingtoall: " <<engine.reg._entityCount << std::endl;

      
      if (post.t == 5) {
        engine.instanciatePatron<BossOnePatron>(500.0f, 0.0f, 303);
        for (auto &&i : this->_players) {
          engine.ServerSendUdp<spawn_boss_t>(i.udp_id, SPAWN_BOSS, {303, 500.0f, 0.0f});
        }
      }
      if (post.t == 6) {
        for (auto &&i : this->_players) {
          engine.ServerSendUdp<kill_monster_t>(i.udp_id, KILL_MONSTER, {303});
        }
      }
      std::cout << "-----------------\n";
    });


    
    _engine.registerComponent<zef::comp::position>();
    _engine.registerComponent<zef::comp::vector>();
    _engine.registerComponent<zef::comp::drawable>();
    _engine.registerComponent<zef::comp::collidable>();
    _engine.registerComponent<Owner>();
    _engine.registerComponent<Health>();
    _engine.registerComponent<Lifetime>();
    _engine.registerComponent<zef::comp::event_listener>();
    _engine.registerComponent<Player>();
    _engine.registerComponent<BackGround>();
    _engine.registerComponent<zef::comp::replicable>();
    _engine.registerComponent<VectorHolder>();
    _engine.registerComponent<Monster>();
    _engine.registerComponent<Laser>();
    _engine.registerComponent<Ship>();
    _engine.registerComponent<TurretTurnRate>();
    _engine.registerComponent<Damaged>();
    _engine.registerComponent<SinusoidalMotion>();
    _engine.registerComponent<MoveCamera>();
    _engine.registerComponent<SinusoidalAboveMotion>();
    _engine.registerComponent<Plane>();
    _engine.registerComponent<Robot>();
    _engine.registerComponent<Boss>();

    _engine.addSystem<>("zefir", zef::sys::handle_server);
    _engine.addSystem<Lifetime>("zefir", lifetime_system);
    _engine.addSystem<zef::comp::position, zef::comp::vector>("zefir", zef::sys::move);

    _engine.addSystem<zef::comp::collidable, zef::comp::position>("zefir", zef::sys::check_collidables);
    _engine.addSystem<zef::comp::event_listener>("zefir", zef::sys::resolveEvent);

    _engine.addSystem<
    Health, zef::comp::replicable, Monster
    >("zefir", [this](zef::Engine& engine, ecs::sparse_array<Health>& hss, ecs::sparse_array<zef::comp::replicable>& rps, ecs::sparse_array<Monster>& mss){
      for (auto &&[i, h, r, m]: ecs::indexed_zipper(hss, rps, mss)) {
        if (h.hp <= 0) {
          for (auto &i : this->_players) engine.ServerSendUdp<kill_monster_t>(i.udp_id, KILL_MONSTER, {r._id});
          engine.sendEvent<OnDeath>(i);
        }
      }
    });

    _engine.addSystem<
    Health, zef::comp::replicable, Ship
    >("zefir", [this](zef::Engine& engine, ecs::sparse_array<Health>& hss, ecs::sparse_array<zef::comp::replicable>& rps, ecs::sparse_array<Ship>& mss){
      for (auto &&[i, h, r, s]: ecs::indexed_zipper(hss, rps, mss)) {
        if (h.hp <= 0) {
          for (auto &i : this->_players) engine.ServerSendUdp<kill_ally_t>(i.udp_id, KILL_ALLY, {r._id});
          engine.ServerSendUdp<kill_t>(this->_players[r._id].udp_id, KILL, {});
          engine.sendEvent<OnDeath>(i);
          std::cout << "h\n";
        }
      }
    });
    


    //_engine.addSystem<>("zefir", [](zef::Engine& engine){std::cout << engine.elapsed.count() << std::endl;});

    _engine.addSystem<Plane, zef::comp::replicable ,zef::comp::position>("zefir", [this](zef::Engine& engine, ecs::sparse_array<Plane>& pls, ecs::sparse_array<zef::comp::replicable>& rss, ecs::sparse_array<zef::comp::position>& pss) {
      for (auto &&[i, pl, r, pos] : ecs::indexed_zipper(pls, rss, pss)) {
        int rd = rand() % 100;
        if (rd == 90) {
          std::cout << "shootingp" << std::endl;
          for (auto &i : this->_players) engine.ServerSendUdp<plane_shoot_t>(i.udp_id, PLANE_SHOOT, {r._id, -5.0f,  -1.0f});
          engine.instanciatePatron<EnemyBulletPatron>(pos.x, pos.y, -5.0f,  -1.0f);
        }
      }
    });

    _engine.addSystem<Robot, zef::comp::replicable ,zef::comp::position, zef::comp::vector>("zefir", [this](zef::Engine& engine, ecs::sparse_array<Robot>& pls, ecs::sparse_array<zef::comp::replicable>& rss, ecs::sparse_array<zef::comp::position>& pss, ecs::sparse_array<zef::comp::vector>& vss) {
      for (auto &&[i, pl, r, pos, vec] : ecs::indexed_zipper(pls, rss, pss, vss)) {
        int rd = rand() % 100;
        float ny = static_cast<float>((rand() % 12) - 6);
        
        if (rd == 45) {
          vec.y = ny;
          
          for (auto &i : this->_players) engine.ServerSendUdp<robot_new_dir_t>(i.udp_id, ROBOT_NEW_DIR, {r._id, 0.0f, ny, pos.x, pos.y});
        }
        
        if (pos.y > 300 || pos.y < -300) {
          vec.y = -vec.y;
          for (auto &i : this->_players) engine.ServerSendUdp<robot_new_dir_t>(i.udp_id, ROBOT_NEW_DIR, {r._id, 0.0f, vec.y, pos.x, pos.y});
        }
        int rd2 = rand() % 200;
        if (rd2 == 5) {
          
          engine.instanciatePatron<RobotBulletPatron>(pos.x, pos.y);
          for (auto &i : this->_players) engine.ServerSendUdp<robot_shoot_t>(i.udp_id, ROBOT_SHOOT, {r._id, pos.x, pos.y});
        }
        
      }
    });

    _engine.addSystem<Ship, zef::comp::replicable, Health>("zefir", [this](zef::Engine& engine, ecs::sparse_array<Ship>& sss, ecs::sparse_array<zef::comp::replicable>& rps, ecs::sparse_array<Health>& hhs) {
        for (auto &&[i, s, r, hp]: ecs::indexed_zipper(sss, rps, hhs)) {
          if (hp.up) {
            std::cout << "needupdate" << std::endl;

            engine.ServerSendUdp<update_hp_t>(this->_players[r._id].udp_id, UPDATE_HP, {hp.hp});

            for (auto &i : this->_players)  engine.ServerSendUdp<ally_update_hp_t>(i.udp_id, ALLY_UPDATE_HP, {r._id ,hp.hp});
            hp.up = false;
          }
        }
    });

    _engine.addSystem<zef::comp::replicable, Boss, zef::comp::position>("zefir", [this](zef::Engine& engine, ecs::sparse_array<zef::comp::replicable>& rps, ecs::sparse_array<Boss>& hhs, ecs::sparse_array<zef::comp::position>& pss) {
        for (auto &&[i, r, b, pos]: ecs::indexed_zipper(rps, hhs, pss)) {
          std::cout<< "kkk" << r._id << "\n";
          int rd = rand() % 100;
          if (rd == 89) {
            for (auto &i : this->_players)  engine.ServerSendUdp<boss_shoot_t>(i.udp_id, BOSS_SHOOT, {r._id});
            for (size_t i = 0; i < 5; i++)
              engine.instanciatePatron<RobotBulletPatron>(pos.x - 50 - (i * 80),
                                                            pos.y);
          }
        }
    });

    _engine.addSystem<>("zefir", [](zef::Engine& engine) {
      //std::cout << engine.elapsed.count() << std::endl;
      if (engine.elapsed.count() < 16000)
        std::this_thread::sleep_for(std::chrono::microseconds(16000 - engine.elapsed.count()));
    });
    register_tcp_game_cmd();
    register_udp_game_cmd();


    _player_uuid = player_uuid;
    _engine.initServer(udp_port, tcp_port);
    std::cout << "wtddddd : " << _players.size() << std::endl;
    _engine.newLoadScene<LevelScene>();
    _engine.run();
  }

  

  void Game::init_game(std::vector<std::string> player_uuid, int tcp_port,
                       int udp_port) {
    _games.push_back(std::thread([this, player_uuid, tcp_port, udp_port]() {
      this->launch_game(player_uuid, tcp_port, udp_port);
    }));
  }

  Game::~Game() {
  }

}  // namespace rtype
