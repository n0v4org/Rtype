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
#include "LobbyPatron.hpp"

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


class LobbyScene{
public:
  static void loadScene(zef::Engine& engine) {

    engine.instanciatePatron<MenuBackgroundPatron>();
    engine.instanciatePatron<ButtonPatron>(
        850.0f, -450.0f,
        "returnButton",
        [](zef::Engine &engine, size_t self) {
            engine.loadScene("lobbyList");
        },
        210.0f, 210.0f, 0.5f, 0.5f
    );
    engine.instanciatePatron<TextButtonPatron>(
        -650.f,-400.f,
        "emptyButton",
        "Jonfre","eth",42,
        [](zef::Engine &engine, size_t self) {
            engine.loadScene("option");
        },
        420.0f, 170.0f, 1.f, 1.f
    );
    engine.instanciatePatron<TextButtonPatron>(
        550.f, 400.f,
        "emptyButton",
        "READY","eth",72,
        [](zef::Engine &engine, size_t self) {
            engine.fetchEntityComponent<zef::comp::drawable>(self).rgba = {0.5,1,0.5,1};
            engine.fetchEntityComponent<zef::comp::drawableText>(self).rgba = {0,1,0,1};
        },
        420.0f, 170.0f, 1.f, 1.f
    );
    engine.instanciatePatron<TitlePatron>(
        -650.0f, 60.0f,
        "Window",
        0.6f, 0.4f
    );

    engine.instanciatePatron<LobbyPlayerSlot>(-100.0f,-250.0f,"tristre","lobbyPlayer1",1,true,false,false);
    engine.instanciatePatron<LobbyPlayerSlot>(-150.0f,100.0f,"","lobbyPlayer2",1,true,true,false);
    engine.instanciatePatron<LobbyPlayerSlot>(0.0f, 350.0f,"isacre","lobbyPlayer3",1,false,true,false);
    engine.instanciatePatron<LobbyPlayerSlot>(550.0f, 0.0f,"#EIPCPPVITE","lobbyPlayer4",1,true,true,false);
    engine.instanciatePatron<LobbyPlayerSlot>(400.0f,-300.0f,"I C S","lobbyPlayer0",1,false,false,false);
  }
};

class LobbyListScene {
public:
    static void loadScene(zef::Engine& engine) {
    	engine.instanciatePatron<MenuBackgroundPatron>();
        engine.instanciatePatron<ButtonPatron>(
            850.0f, -450.0f,
            "returnButton",
            [](zef::Engine &engine, size_t self) {
                engine.loadScene("menu");
            },
            210.0f, 210.0f, 0.5f, 0.5f
        );
        engine.instanciatePatron<TextButtonPatron>(
            -550.f,-400.f,
            "emptyButton",
            "Lobby List","eth",42,
            [](zef::Engine &engine, size_t self) {
                engine.loadScene("option");
            },
            420.0f, 170.0f, 1.f, 1.f
        );
        engine.instanciatePatron<TitlePatron>(
            -550.0f, 100.0f,
            "Window",
            0.8f, 0.5f
        );

        std::vector<std::string> names = {"Pierre", "Jonfre", "JOE(tek4)", "ANTOINETTE"};
        int slots = 1;
        for (int i = 0; i < 3; i += 1) {
        slots = rand() % 5;
        engine.instanciatePatron<LobbyListTabPatron>(
            -550.0f, -80.0f + (i * 180.0f),
            8, names[rand() % 4],
            slots, rand() % slots,
            [](zef::Engine &engine, size_t self) {
                engine.loadScene("lobby");
            }
        );
        }
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
                engine.loadScene("lobbyList");
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
            1.0f, 0.8f, 1
        );

        engine.instanciatePatron<ButtonPatron>(
            0.0f, -200.0f,
            "Sound_BTN",
            [](zef::Engine &engine, size_t self) {
                std::string vol = "Volume";
                int currentVolume = std::stoi(engine.GraphLib->getSetting(vol).c_str());
                engine.GraphLib->playSound("checkSound");
            },
            210.0f, 210.0f, 0.75f, 0.75f
        );
        
        engine.instanciatePatron<ButtonPatron>(
            -250.0f, -200.0f,
            "Backward_BTN",
            [](zef::Engine &engine, size_t self) {
                std::cout << "minus clicked!" << std::endl;
                std::string vol = "Volume";
                int currentVolume = std::stoi(engine.GraphLib->getSetting(vol).c_str());
                std::cout << currentVolume << std::endl;
                int newVolume;
                if (currentVolume <= 0) {
                    newVolume = 0;
                } else {
                    newVolume = currentVolume - 5;
                    engine.GraphLib->playSound("checkSound");
                }
                engine.GraphLib->updateSettings("Volume", std::to_string(newVolume));
                std::cout << newVolume << std::endl;
            },
            210.0f, 210.0f, 0.75f, 0.75f
        );

        engine.instanciatePatron<ButtonPatron>(
            250.0f, -200.0f,
            "Forward_BTN",
            [](zef::Engine &engine, size_t self) {
                std::cout << "plus clicked!" << std::endl;
                std::string vol = "Volume";
                int currentVolume = std::stoi(engine.GraphLib->getSetting(vol).c_str());
                std::cout << currentVolume << std::endl;
                int newVolume;
                if (currentVolume >= 100) {
                    newVolume = 100;
                } else {
                    newVolume = currentVolume + 5;
                    engine.GraphLib->playSound("checkSound");
                }
                engine.GraphLib->updateSettings("Volume", std::to_string(newVolume));
                std::cout << newVolume << std::endl;
            },
            210.0f, 210.0f, 0.75f, 0.75f
        );

        engine.instanciatePatron<SoundBarPatron>(
            0.0f, -50.0f
        );
    }
};

#endif /* !SCENES_HPP_ */
