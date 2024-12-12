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
#include "../../utils/inputsUtils.hpp"
#include "events.hpp"

namespace zef
{
    namespace sys
    {

        void system_constrollables(zef::Engine& engine, ecs::sparse_array<zef::comp::controllable>& controllables);
        void update_user_inputs(zef::Engine& engine);
        void handleclickable(zef::Engine& engine, ecs::sparse_array<zef::comp::clickable>& clickables, ecs::sparse_array<zef::comp::position>& positions);
    } // namespace sys
} // namespace zef


#endif // ENGINE_MODULES_CONTROLLER_SYSTEMS_HPP_
