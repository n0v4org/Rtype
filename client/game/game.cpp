/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** game
*/

#include "Engine.hpp"
#include "Scenes.hpp"
#include "systems.hpp"


#include "modules/display/systems.hpp"
#include "modules/movement/systems.hpp"
#include "modules/controller/systems.hpp"
#include "asio.hpp"

void runClient(/*port*/) {
    zef::Engine engine;

    engine.initGraphLib("Assets", "");

    engine.GraphLib->saveAnimation("ship", "image", 0, 0, 65, 66);

    
    engine.registerComponent<zef::comp::position>();
    engine.registerComponent<zef::comp::vector>();
    engine.registerComponent<zef::comp::drawable>();
    engine.registerComponent<zef::comp::collidable>();
    engine.registerComponent<Owner>();
    engine.registerComponent<Lifetime>();
    engine.registerComponent<zef::comp::event_listener>();
    engine.registerComponent<zef::comp::controllable>();
    engine.registerComponent<Player>();
    

    //engine.addSystem<>(entitycountdisplay);

    engine.addSystem<>(zef::sys::update_user_inputs);
    engine.addSystem<Lifetime>(lifetime_system);
    engine.addSystem<zef::comp::vector, Player>(resetPlayerMovement);
    engine.addSystem<zef::comp::controllable>(zef::sys::system_constrollables);
    engine.addSystem<zef::comp::event_listener>(zef::sys::resolveEvent);
    engine.addSystem<zef::comp::vector>(zef::sys::normalize_velocity_vectors);
    engine.addSystem<zef::comp::position, zef::comp::vector>(zef::sys::move);
    engine.addSystem<zef::comp::collidable, zef::comp::position>(zef::sys::check_collidables);
    engine.addSystem<zef::comp::event_listener>(zef::sys::resolveEvent);


    engine.addSystem<zef::comp::drawable>(zef::sys::update_animations);
    engine.addSystem<zef::comp::drawable, zef::comp::position>(zef::sys::draw_drawables);

    

    engine.registerScene<LevelScene>("level");
    engine.registerScene<LobbyScene>("lobby");
    engine.loadScene("level");

    engine.run();
}