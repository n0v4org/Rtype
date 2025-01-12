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

    engine.initGraphLib("Assets", "");

    engine.GraphLib->saveAnimation("menu", "menu", 0, 0, 1920, 1080);
    engine.GraphLib->saveAnimation("play", "play", 0, 0, 200, 100);

    engine.registerComponent<zef::comp::position>();
    engine.registerComponent<zef::comp::drawable>();
    engine.registerComponent<zef::comp::clickable>();
    engine.registerComponent<zef::comp::event_listener>();
    engine.registerComponent<BackGround>();

    engine.addSystem<zef::comp::clickable, zef::comp::position>("zefir", zef::sys::handleclickable);
    engine.addSystem<zef::comp::drawable>("zefir", zef::sys::update_animations);
    engine.addSystem<zef::comp::drawable, zef::comp::position>("zefir", zef::sys::draw_drawables);

    engine.registerScene<MenuScene>("menu");
    engine.loadScene("menu");

    engine.run();
}

