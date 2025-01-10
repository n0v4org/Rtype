/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** game
*/

#include <string>
#include "Engine.hpp"
#include "Scenes.hpp"
#include "systems.hpp"

#include "modules/display/systems.hpp"
#include "modules/movement/systems.hpp"
#include "modules/network/systems.hpp"
#include "modules/controller/systems.hpp"

// #include "asio.hpp" 
// #include "CommonCommands.hpp" 

void runClient(int /*sport*/, int /*cport*/, std::string /*ip*/) {
    zef::Engine engine;

    engine.initGraphLib("Assets", "");
    engine.GraphLib->saveAnimation("menu", "menu", 0, 0, 1920, 1080);

    engine.registerComponent<zef::comp::position>();
    engine.registerComponent<zef::comp::drawable>();
    engine.registerComponent<BackGround>(); 

    engine.addSystem<>("zefir", zef::sys::update_user_inputs);

    engine.addSystem<zef::comp::drawable>("zefir", zef::sys::update_animations);

    engine.addSystem<zef::comp::drawable, zef::comp::position>(
        "zefir", zef::sys::draw_drawables
    );

    engine.registerScene<MenuScene>("menu");

    engine.loadScene("menu");

    engine.run(); 
}
