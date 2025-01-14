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
#include "EnemyBulletPatron.hpp"
#include "BlastPatron.hpp"
#include "events.hpp"
#include "MenuBackgroundPatron.hpp"
#include "ButtonPatron.hpp"
#include "TitlePatron.hpp"

class LevelScene {
public:
  static void loadScene(zef::Engine& engine) {
    // engine.GraphLib->moveCamera(0, 0, 0.5);
    engine.instanciatePatron<PlayerPatron>(0.0f, 150.0f, 0);
    // ecs::Entity ally = engine.instanciatePatron<AllyPatron>(0.0f, -150.0f);
    // engine.instanciatePatron<EnemyPatron>(600.0f, -150.0f);
    engine.instanciatePatron<BackgroundPatron>(0.0f, 0.0f);
    engine.instanciatePatron<BackgroundPatron>(1920.0f, 0.0f);
    engine.instanciatePatron<BlastPatron>(0.0f, 0.0f, 1.0f);
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

        engine.instanciatePatron<TitlePatron>(
            0.0f, -250.0f,
            "Type_Logo",
            1.5f, 1.5f
        );

        engine.instanciatePatron<ButtonPatron>(
            0.0f, 100.0f,
            "Start",
            [](zef::Engine &engine, size_t self) {
                engine.loadScene("game");
            },
            410.0f, 121.0f
        );

        engine.instanciatePatron<ButtonPatron>(
            0.0f, 300.0f,
            "Exit",
            [](zef::Engine &engine, size_t self) {
                std::cout << "Quit clicked!" << std::endl;
            },
            410.0f, 121.0f
        );

        engine.instanciatePatron<ButtonPatron>(
            850.0f, -450.0f,
            "Settings",
            [](zef::Engine &engine, size_t self) {
                std::cout << "Settings clicked!" << std::endl;
                engine.loadScene("option");
            },
            210.0f, 210.0f, 0.5f, 0.5f
        );
    }
};

class OptionScene {
public:
    static void loadScene(zef::Engine &engine) {
        engine.instanciatePatron<MenuBackgroundPatron>();

        engine.instanciatePatron<ButtonPatron>(
            -850.0f, -450.0f,
            "Backward_BTN",
            [](zef::Engine &engine, size_t self) {
                std::cout << "return clicked!" << std::endl;
                engine.loadScene("menu");
            },
            210.0f, 210.0f, 0.5f, 0.5f
        );

        engine.instanciatePatron<TitlePatron>(
            0.0f, 0.0f,
            "Window",
            1.0f, 0.70f
        );

        engine.instanciatePatron<TitlePatron>(
            0.0f, -440.0f,
            "Information",
            1.0f, 0.8f
        );

        engine.instanciatePatron<TitlePatron>(
            0.0f, -200.0f,
            "Sound_BTN",
            0.75f, 0.75f
        );
        
        engine.instanciatePatron<ButtonPatron>(
            -250.0f, -200.0f,
            "Backward_BTN",
            [](zef::Engine &engine, size_t self) {
                std::cout << "minus clicked!" << std::endl;
            },
            210.0f, 210.0f, 0.75f, 0.75f
        );

        engine.instanciatePatron<ButtonPatron>(
            250.0f, -200.0f,
            "Forward_BTN",
            [](zef::Engine &engine, size_t self) {
                std::cout << "plus clicked!" << std::endl;
                std::string vol = "Volume";
                int currentVolume = std::stoi(engine.GraphLib->getSetting(vol));
                std::cout << currentVolume << std::endl;
                int newVolume = currentVolume + 2;
                engine.GraphLib->updateSettings("Volume", std::to_string(newVolume));
                std::cout << newVolume << std::endl;
            },
            210.0f, 210.0f, 0.75f, 0.75f
        );

        engine.instanciatePatron<SoundBarPatron>(
            0.0f, 0.0f
        );
    }
};

#endif /* !SCENES_HPP_ */
