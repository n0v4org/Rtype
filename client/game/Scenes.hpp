/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** Scenes
*/

#ifndef SCENES_HPP_
#define SCENES_HPP_

#include "Engine.hpp"

#include "PlayerPatron.hpp"
#include "AllyPatron.hpp"
#include "BulletPatron.hpp"
#include "EnemyPatron.hpp"
#include "EnemyTurretPatron.hpp"
#include "BackgroundPatron.hpp"
#include "EnemyBulletPatron.hpp"
#include "BlastPatron.hpp"
#include "events.hpp"
#include "EnemyPlanePatron.hpp"
#include "EnemyCrabPatron.hpp"
#include "EnemyRobotPatron.hpp"
#include "BasicWallPatron.hpp"
#include "WaterWallPatron.hpp"
#include "BlockWallPatron.hpp"
#include "BossOnePatron.hpp"
#include "RoomPatron.hpp"

class LevelScene {
public:
  static void loadScene(zef::Engine& engine, std::vector<size_t> allyId) {
    engine.addEntityComponent<MoveCamera>(engine.reg.spawn_entity());
    engine.instanciatePatron<PlayerPatron>(0.0f, 0.0f, 0);
    engine.instanciatePatron<BackgroundPatron>(0.0f, 0.0f);
    engine.instanciatePatron<BackgroundPatron>(1920.0f, 0.0f);

    for (auto &i : allyId)
      engine.instanciatePatron<AllyPatron>(0.f, 0.f, i);
  }
};


  struct testNETtest {};

class TestScene {
public:
  static void loadScene(zef::Engine& engine) {
    const ecs::Entity& e = engine.reg.spawn_entity();
    const ecs::Entity& e2 = engine.reg.spawn_entity();
    const ecs::Entity& e3 = engine.reg.spawn_entity();

    zef::comp::event_listener ev;
    ev.setEvent<testNETtest>([](zef::Engine& engine, size_t self, testNETtest t) {
        engine.ClientSendTcp("LAUNCH_GAME");
        //engine.newLoadScene<LevelScene>();
    });
    engine.addEntityComponent<zef::comp::event_listener>(e, ev);
//
    zef::comp::controllable cont;
    cont.bindOnPressed<testNETtest>(zef::utils::Space);
    engine.addEntityComponent<zef::comp::controllable>(e, cont);
  }
};

class TestScene2 {
public:
  static void loadScene(zef::Engine& engine) {
    engine.addEntityComponent<MoveCamera>(engine.reg.spawn_entity());
    engine.instanciatePatron<PlayerPatron>(0.0f, 0.0f, 0);
    engine.instanciatePatron<BackgroundPatron>(0.0f, 0.0f);
    engine.instanciatePatron<BackgroundPatron>(1920.0f, 0.0f);
    engine.instanciatePatron<RoomPatron>("../Assets/config/bossRoomEx.txt", 0.f, 0.f);

  }
};

class LobbyScene {
public:
  static void loadScene(zef::Engine& engine) {
  }
};

#endif /* !SCENES_HPP_ */
