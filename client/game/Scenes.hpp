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

class LevelScene {
public:
  static void loadScene(zef::Engine& engine) {
    engine.addEntityComponent<MoveCamera>(engine.reg.spawn_entity());
    // engine.GraphLib->moveCamera(0, 0, 0.5);
    engine.instanciatePatron<PlayerPatron>(0.0f, 150.0f, 0);
    // engine.instanciatePatron<EnemyPatron>(600.0f, -150.0f);
    engine.instanciatePatron<BackgroundPatron>(0.0f, 0.0f);
    engine.instanciatePatron<BackgroundPatron>(1920.0f, 0.0f);
    // engine.instanciatePatron<AllyPatron>(0.0f, 0.0f, 4);
    engine.instanciatePatron<EnemyTurretPatron>(0.0f, 0.0f, false, true);
    ecs::Entity e = engine.instanciatePatron<EnemyPlanePatron>(500.0f, 0.0f, 1);
    engine.sendEvent<SetEnemyVectorEvent>(e, -1.0f, 0.0f);
    engine.sendEvent<PlaneShootEvent>(e, -1.0f, 0.0f);
    engine.sendEvent<TurretTurn>(
        engine.instanciatePatron<EnemyTurretPatron>(0.0f, 100.0f, true, false),
        1);
    ecs::Entity crab =
        engine.instanciatePatron<EnemyCrabPatron>(400.0f, 200.0f, 2);
    engine.sendEvent<SetEnemyVectorEvent>(crab, 0.0f, 1.0f);
    ecs::Entity robo =
        engine.instanciatePatron<EnemyRobotPatron>(600.f, 100.f, 2);
    engine.sendEvent<SetEnemyVectorEvent>(robo, 0.f, 0.f);
    engine.sendEvent<RobotShoot>(robo);
    engine.instanciatePatron<BasicWallPatron>(-500.f, 0.f, 7.0f, 5.0f);
    engine.instanciatePatron<WaterWallPatron>(0.f, 0.f, 10.0f, 3.0f);
    engine.instanciatePatron<BlockWallPatron>(0.f, 500.f, 15.0f, 3.0f);
    engine.instanciatePatron<BlockWallPatron>(0.f, -500.f, 15.0f, 3.0f, 180.f);
    // engine.sendEvent<SetEnemyPos>(crab, -500.0f, 200.0f);
    //  engine.instanciatePatron<BackgroundPatron>(470.0f, 0.0f);
  }
};

class LobbyScene {
public:
  static void loadScene(zef::Engine& engine) {
  }
};

#endif /* !SCENES_HPP_ */
