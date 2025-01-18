/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** Scenes
*/

#ifndef SCENES_HPP_
#define SCENES_HPP_

#include "Engine.hpp"

#include "BulletPatron.hpp"
#include "events.hpp"
#include "PlanePatron.hpp"
#include "GamerT.hpp"

class LevelScene {
public:
  static void loadScene(zef::Engine& engine, std::vector<game_player_t> _players) {
    std::cout << "player ========= " << _players.size() << std::endl;
    for (int i = 0; i <= _players.size(); i++) {
      std::cout << "pkkkkkkkkkkkkkkkkkkkkkkkkkkkkk" << std::endl;
      engine.instanciatePatron<AllyPatron>(0.f, 0.f, i);
    }
    // engine.instanciatePatron<PlayerPatron>(0.0f, 150.0f)
  }
};

class LobbyScene {
public:
  static void loadScene(zef::Engine& engine) {
  }
};

#endif /* !SCENES_HPP_ */
