/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** controllable
*/

#ifndef ENGINE_MODULES_CONTROLLER_SYSTEMS_HPP_
#define ENGINE_MODULES_CONTROLLER_SYSTEMS_HPP_

#include "../../Engine.hpp"
#include "components.hpp"
#include "../../ecs/indexed_zipper.hpp"

namespace zef
{
    namespace sys
    {
        void system_constrollables(zef::Engine& engine, ecs::sparse_array<zef::comp::controllable>& controllables) {
            for (auto &&[i, co] : ecs::indexed_zipper(controllables)) {
                zef::UserInputs ui = engine.getUserInputs();
                
                for (auto& k : ui.keyboard.PressedKeys) {
                    if (co._pressed.find(k) != co._pressed.end()) {
                        co._pressed[k](engine, i);
                    }    
                }
                for (auto& k : ui.keyboard.ReleasedKeys) {
                    if (co._released.find(k) != co._released.end()) {
                        co._released[k](engine, i);
                    }    
                }



            }
        }
    } // namespace sys
} // namespace zef


#endif // ENGINE_MODULES_CONTROLLER_SYSTEMS_HPP_
