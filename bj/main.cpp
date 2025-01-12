/*
** EPITECH PROJECT, 2025
** RTYPE
** File description:
** main
*/


#include "Engine.hpp"


#include "modules/display/systems.hpp"
#include "modules/controller/systems.hpp"
#include "modules/movement/systems.hpp"

#include "components.hpp"
#include "systems.hpp"

#include "scenes.hpp"


int main() {

    zef::Engine engine;


    engine.initGraphLib("../bjAssets", "");

    engine.GraphLib->saveAnimation("backGround", "bg", 0, 0, 1920, 1080);
    engine.GraphLib->saveAnimation("bttn", "button", 0, 0, 200, 100);
    engine.GraphLib->saveAnimation("bjbg", "bjbg", 0, 0, 1000, 513);

    for (int i = 0; i < 13; i++) {
    for (int j = 0; j < 4; j++) {
        engine.GraphLib->saveAnimation("card " + std::to_string(i) + " " + std::to_string(j), "CuteCards", i * 100, j, 100, 144);
        std::cout << "card " + std::to_string(i) + " " + std::to_string(j) << std::endl;
    }
    }
    
    engine.registerComponent<zef::comp::event_listener>();
    engine.registerComponent<zef::comp::clickable>();
    engine.registerComponent<zef::comp::position>();
    engine.registerComponent<zef::comp::drawable>();



    engine.addSystem<>("zefir", zef::sys::update_user_inputs);
    engine.addSystem<zef::comp::clickable, zef::comp::position>("zefir", zef::sys::handleclickable);
    engine.addSystem<zef::comp::event_listener>("zefir", zef::sys::resolveEvent);
    engine.addSystem<zef::comp::drawable>("zefir", zef::sys::update_animations);
    engine.addSystem<zef::comp::drawable, zef::comp::position>("zefir", zef::sys::draw_drawables);


    engine.registerScene<MenuScene>("menu");
    engine.registerScene<GameScene>("game");
    engine.loadScene("menu");

    engine.run();
}