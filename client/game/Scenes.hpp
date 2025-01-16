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

class LevelScene {
public:
  static void loadScene(zef::Engine& engine) {
    // engine.GraphLib->moveCamera(0, 0, 0.5);
    engine.instanciatePatron<PlayerPatron>(0.0f, 150.0f, 0);
    // ecs::Entity ally = engine.instanciatePatron<AllyPatron>(0.0f, -150.0f);
    // engine.instanciatePatron<EnemyPatron>(600.0f, -150.0f);
    engine.instanciatePatron<BackgroundPatron>(0.0f, 0.0f);
    engine.instanciatePatron<BackgroundPatron>(1920.0f, 0.0f);
    engine.instanciatePatron<AllyPatron>(0.0f, 0.0f);
    engine.instanciatePatron<EnemyTurretPatron>(0.0f, 0.0f, false, true);
    ecs::Entity e = engine.instanciatePatron<EnemyPlanePatron>(500.0f, 0.0f, 1);
    engine.sendEvent<SetEnemyVectorEvent>(e, -1.0f, 0.0f);
    engine.sendEvent<PlaneShootEvent>(e, -1.0f, 0.0f);
    engine.sendEvent<TurretTurn>(engine.instanciatePatron<EnemyTurretPatron>(0.0f, 100.0f, true, false), 1);
    ecs::Entity crab = engine.instanciatePatron<EnemyCrabPatron>(400.0f, 200.0f, 2);
    engine.sendEvent<SetEnemyVectorEvent>(crab, 0.0f, 1.0f);
    //engine.sendEvent<SetEnemyPos>(crab, -500.0f, 200.0f);
    // engine.instanciatePatron<BackgroundPatron>(470.0f, 0.0f);
  }
};

class LobbyScene {
public:
  static void loadScene(zef::Engine& engine) {
  }
};

#endif /* !SCENES_HPP_ */
