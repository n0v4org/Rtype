/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** game
*/

#include <string>
#include <iostream>

#include "Game.hpp"

namespace rtype {

  Game::Game() {
  }

  void Game::RegisterGameCmd() {
  }

  void Game::launch_game(std::vector<std::string> player_uuid, int tcp_port,
              int udp_port) {

    std::cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" << std::endl;
    
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

    _engine.addSystem<>("zefir", zef::sys::handle_server);
    _engine.addSystem<Ship, zef::comp::position>("zefir", showShipPos);


    register_tcp_game_cmd();
    register_udp_game_cmd();


    _player_uuid = player_uuid;
    _engine.initServer(udp_port, tcp_port);
    _engine.newLoadScene<LevelScene>(_players);
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
