/*
** EPITECH PROJECT, 2025
** r-type
** File description:
** game
*/

#include "Engine.hpp"
#include "Scenes.hpp"         
#include "systems.hpp" 
#include "modules/display/systems.hpp"
#include "modules/movement/systems.hpp"
#include "components.hpp"
#include "modules/display/components.hpp"
#include "modules/movement/components.hpp"
#include "modules/controller/systems.hpp"
#include "events.hpp"

void runClient(int /*sport*/, int /*cport*/, std::string /*ip*/) {
    zef::Engine engine;

    engine.initGraphLib("../Assets", "");

    engine.GraphLib->saveAnimation("menu", "menu", 0, 0, 1920, 1080);
    engine.GraphLib->saveAnimation("Start", "Start", 0, 0, 410, 121);
    engine.GraphLib->saveAnimation("Exit", "Exit", 0, 0, 410, 121);
    engine.GraphLib->saveAnimation("Settings", "Settings", 0, 0, 210, 210);
    engine.GraphLib->saveAnimation("Type_Logo.png", "Type_Logo.png", 0, 0, 326, 119);


    engine.registerComponent<zef::comp::position>();
    engine.registerComponent<zef::comp::drawable>();
    engine.registerComponent<zef::comp::clickable>();
    engine.registerComponent<zef::comp::event_listener>();
    engine.registerComponent<BackGround>();

    engine.addSystem<>("zefir", zef::sys::update_user_inputs);
    engine.addSystem<zef::comp::clickable, zef::comp::position>("zefir", zef::sys::handleclickable);
    engine.addSystem<zef::comp::event_listener>("zefir", zef::sys::resolveEvent);
    engine.addSystem<zef::comp::drawable>("zefir", zef::sys::update_animations);
    engine.addSystem<zef::comp::drawable, zef::comp::position>("zefir", zef::sys::draw_drawables);

    engine.registerScene<MenuScene>("menu");
    engine.loadScene("menu");

    engine.run();
}

