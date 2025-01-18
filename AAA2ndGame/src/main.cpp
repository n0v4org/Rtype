/*
** EPITECH PROJECT, 2025
** RTYPE
** File description:
** main
*/

#include <random>

#include "Engine.hpp"
#include "AModule.hpp"
#include "systems.hpp"
#include "modules/controller/systems.hpp"


#include "scripts.hpp"


class zfr : public zef::AModule<
    zef::Component<compTest, int>,
    zef::Component<NewDrawable, std::string, float, int>,
    zef::Component<Position, float, float>,
    zef::Component<Vector, float, float>,
    zef::Component<Text, std::string, int>,
    zef::Component<Clickable, int, int>,
    zef::Component<Respawn, int>,
    zef::Component<Score>,
    zef::Component<Duck>,
    zef::Component<FinalScore>

> {

    void registerSystems(zef::Engine& engine) {
        engine.addSystem<>("zefir", zef::sys::update_user_inputs);
        engine.addSystem<NewDrawable, Position>("zefir", drawNewDrawable);
        engine.addSystem<Text, Position>("zefir", drawText);
        engine.addSystem<Position, Vector>("zefir", newMove);
        engine.addSystem<Clickable, Position>("zefir", handleClickable);
        engine.addSystem<zef::comp::new_event_listener>("zefir", zef::sys::nresolveEvent);
        engine.addSystem<Respawn, Position, Vector>("zefir", handleRespawn);
        engine.addSystem<Score, Text>("zefir", handleScore);
        engine.addSystem<Text, FinalScore>("zefir", handleFinalScore);
        engine.addSystem<Duck, Position, Vector>("zefir", bounceDuck);
    }
};

int main() {

    srand(time(NULL));
    zef::Engine engine;
    engine.initGraphLib("../AAA2ndGame/Assets", "");

    engine.registerComponent<zef::comp::new_event_listener>();

    engine._runtime_modules["zefir"] = std::unique_ptr<zef::IModule>(new zfr);
    engine._runtime_modules["zefir"]->registerComponents(engine);
    engine._runtime_modules["zefir"]->registerSystems(engine);
    Scripts sc;
    engine._script_map = sc._scr;



    engine.loadPatron("../AAA2ndGame/Assets/patronBg.json");
    engine.loadPatron("../AAA2ndGame/Assets/patronBgMenu.json");
    engine.loadPatron("../AAA2ndGame/Assets/patronBttn.json");
    engine.loadPatron("../AAA2ndGame/Assets/patronDuck.json");
    engine.loadPatron("../AAA2ndGame/Assets/patronGrass.json");
    engine.loadPatron("../AAA2ndGame/Assets/patronScore.json");
    engine.loadPatron("../AAA2ndGame/Assets/patronScoreBoard.json");


    engine.registerScene("../AAA2ndGame/Assets/sceneMenu.json");
    engine.registerScene("../AAA2ndGame/Assets/sceneGame.json");
    engine.registerScene("../AAA2ndGame/Assets/sceneGameOver.json");

    engine.loadSceneConfig("Menu");

    engine.run();
    return 0;
}