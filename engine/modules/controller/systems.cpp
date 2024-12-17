#include "systems.hpp"

void zef::sys::system_constrollables(
    zef::Engine& engine,
    ecs::sparse_array<zef::comp::controllable>& controllables) {
        
            //zef::utils::UserInputs engine._user_inputs = engine.getUserInputs();
            if (controllables.size () == 0)
                return;
            for (auto &&[i, co] : ecs::indexed_zipper(controllables)) {
                
                for (auto& k : engine.getUserInputs().keyboard._released) {
                    if (co._released.find(k) != co._released.end()) {
                        co._released[k](engine, i);
                    }    
                }
                for (auto& k : engine.getUserInputs().keyboard._pressed) {
                    if (co._pressed.find(k) != co._pressed.end()) {
                        co._pressed[k](engine, i);
                    }
                }
                for (auto& [k, state] : engine.getUserInputs().keyboard._key_map) {
                    if (co._is_down.find(k) != co._is_down.end() && state) {
                        co._is_down[k](engine, i);
                    }    
                }
            }
        
}

void zef::sys::update_user_inputs(zef::Engine& engine) {
            engine.updateUserInputs();
        }
void zef::sys::handleclickable(zef::Engine& engine, ecs::sparse_array<zef::comp::clickable>& clickables, ecs::sparse_array<zef::comp::position>& positions) {
            zef::utils::hitbox mouse(0, 0, 1, 1);
            mouse._posX = engine.getUserInputs().mouse.x;
            mouse._posY = engine.getUserInputs().mouse.y;

            for (auto &&[i, clk, pos] : ecs::indexed_zipper(clickables, positions)) {
                for (auto &hitboxe : clk._hitboxes) {
                    hitboxe._posX = pos.x + hitboxe._offsetX - (hitboxe._width / 2);
                    hitboxe._posY = pos.y + hitboxe._offsetY - (hitboxe._height / 2);
                    if (hitboxe.isColliding(mouse)) {
                        engine.sendEvent<evt::hover>(i);
                        if (engine.getUserInputs().mouse._mb_map.at(zef::utils::MouseButtons::Left)) {
                            engine.sendEvent<evt::LeftclickPress>(i);
                        }
                        for (auto mb : engine.getUserInputs().mouse._released) {
                            if (mb == zef::utils::MouseButtons::Left) {
                                engine.sendEvent<evt::LeftclickRelease>(i);
                            }
                        }
                        if (engine.getUserInputs().mouse._mb_map.at(zef::utils::MouseButtons::Right)) {
                            engine.sendEvent<evt::RightclickPress>(i);
                        }
                        for (auto mb : engine.getUserInputs().mouse._released) {
                            if (mb == zef::utils::MouseButtons::Right) {
                                engine.sendEvent<evt::RightclickRelease>(i);
                            }
                        }
                    }
                }
            }
        }