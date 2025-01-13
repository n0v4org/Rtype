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
#include "BackgroundPatron.hpp"
#include "events.hpp"
#include "MenuBackgroundPatron.hpp"
#include "ButtonPatron.hpp"

class LevelScene {
public:
  static void loadScene(zef::Engine& engine) {
    // engine.GraphLib->moveCamera(0, 0, 0.5);
    // engine.instanciatePatron<PlayerPatron>(0.0f, 150.0f);
    // ecs::Entity ally = engine.instanciatePatron<AllyPatron>(0.0f, -150.0f);
    // engine.instanciatePatron<EnemyPatron>(600.0f, -150.0f);
    engine.instanciatePatron<BackgroundPatron>(0.0f, 0.0f);
    engine.instanciatePatron<BackgroundPatron>(1920.0f, 0.0f);
    // engine.instanciatePatron<BackgroundPatron>(470.0f, 0.0f);
  }
};

class LobbyScene {
public:
  static void loadScene(zef::Engine& engine) {
  }
};

class MenuScene {
public:
    static void loadScene(zef::Engine &engine) {
        engine.instanciatePatron<MenuBackgroundPatron>();

        engine.instanciatePatron<ButtonPatron>(
            0.0f, -100.0f,
            "play",
            [](zef::Engine &engine, size_t self) {
                engine.loadScene("game");
            },
            200.0f, 100.0f
        );

        engine.instanciatePatron<ButtonPatron>(
            0.0f, 300.0f,
            "play",
            [](zef::Engine &engine, size_t self) {
                std::cout << "Options clicked!" << std::endl;
            },
            200.0f, 100.0f
        );
    }
};

#endif /* !SCENES_HPP_ */
