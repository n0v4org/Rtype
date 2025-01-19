/*
** EPITECH PROJECT, 2025
** RTYPE
** File description:
** scripts
*/

#ifndef SCRIPTS_HPP_
#define SCRIPTS_HPP_


#include "Engine.hpp"
#include "Events.hpp"
#include "components.hpp"

#include <map>

static int __score = 0;

void handleFinalScore(zef::Engine& engine, ecs::sparse_array<Text>& txs, ecs::sparse_array<FinalScore>& fcs) {
    for (auto &&[i, txt, sc]: ecs::indexed_zipper(txs, fcs)) {
        txt._txt = "Score: " + std::to_string(__score);
    }
}


zef::comp::new_event_listener SCRIPT1() {
    zef::comp::new_event_listener evtl;

    evtl.setEvent<int>("event1", [](zef::Engine& engine, size_t self, int val) {
        std::cout << "hohohoh" << std::endl;
    });

    return evtl; 
}

zef::comp::new_event_listener button_play() {
    zef::comp::new_event_listener evtl;

    evtl.setEvent<>("onClick", [](zef::Engine& engine, size_t self) {
        engine.loadSceneConfig("Game");
    });

    return evtl; 
}

zef::comp::new_event_listener button_quit() {
    zef::comp::new_event_listener evtl;

    evtl.setEvent<>("onClick", [](zef::Engine& engine, size_t self) {
        engine.stop();
    });

    return evtl; 
}

zef::comp::new_event_listener duck_script() {
    zef::comp::new_event_listener evtl;

    evtl.setEvent<>("clicked", [__score](zef::Engine& engine, size_t self) {
        engine.fetchEntityComponent<Position>(self)._x = -5000;
        engine.fetchEntityComponent<Vector>(self)._x = 0;
        engine.fetchEntityComponent<Vector>(self)._y = 0;
        engine.addEntityComponent<Respawn>(ecs::Entity(self), rand() % 50 * 100 * 1000);

        for (auto &&[i, sc] : ecs::indexed_zipper(engine.reg.get_components<Score>())) {
            sc._score += 1;
            __score++;
            sc._update = true;
        }
    });

    return evtl; 
}

zef::comp::new_event_listener bg_script() {
    zef::comp::new_event_listener evtl;

    evtl.setEvent<>("clicked", [](zef::Engine& engine, size_t self) {
        for (auto &&[i, s] : ecs::indexed_zipper(engine.reg.get_components<Score>())) {
            if (!s._update)
                engine.loadSceneConfig("GameOver");
        }
    });

    return evtl; 
}


zef::comp::new_event_listener back_to_menu() {
    zef::comp::new_event_listener evtl;

    evtl.setEvent<>("onClick", [](zef::Engine& engine, size_t self) {
        engine.loadSceneConfig("Menu");
    });

    return evtl; 
}

class Scripts  {
    public:
        std::map<std::string, zef::comp::new_event_listener> _scr = {
            {"script1", SCRIPT1()},
            {"play_bttn", button_play()},
            {"quit_bttn", button_quit()},
            {"duck_script", duck_script()},
            {"bg_script", bg_script()},
            {"go_back_to_menu", back_to_menu()}
        };

};

#endif /* !SCRIPTS_HPP_ */
