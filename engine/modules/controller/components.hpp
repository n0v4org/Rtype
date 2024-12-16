/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** controllable
*/

#ifndef ENGINE_MODULES_CONTROLLER_COMPONENTS_HPP_
#define ENGINE_MODULES_CONTROLLER_COMPONENTS_HPP_


#include <map>
#include <functional>
#include <vector>
#include "../../Engine.hpp"
#include "../../utils/hitbox.hpp"
#include "../movement/components.hpp"

namespace zef {

    namespace comp
    {
        class controllable {
            public:
                controllable(){}

                template <typename Events, typename ...T>
                void bindOnPressed(zef::utils::Keys key, T ...args) {
                    _pressed[key] = [args...](Engine& engine, size_t entity){
                        engine.sendEvent<Events>(entity, args...);
                    };
                }

                template <typename Events, typename ...T>
                void bindOnRelease(zef::utils::Keys key, T ...args) {
                    _released[key] = [args...](Engine& engine, size_t entity){
                        engine.sendEvent<Events>(entity, args...);
                    };
                }
                template <typename Events, typename ...T>
                void bindOnDown(zef::utils::Keys key, T ...args) {
                    _is_down[key] = [args...](Engine& engine, size_t entity){
                        engine.sendEvent<Events>(entity, args...);
                    };
                }

                std::map<zef::utils::Keys, std::function<void(Engine &, size_t)>> _pressed;
                std::map<zef::utils::Keys, std::function<void(Engine &, size_t)>> _released;
                std::map<zef::utils::Keys, std::function<void(Engine &, size_t)>> _is_down;
        };

        class clickable {
            public:
                explicit clickable(std::vector<utils::hitbox> hitboxes) : _hitboxes(hitboxes) {

                }

                std::vector<utils::hitbox> _hitboxes;
        };
    } // namespace comp
} // namespace zef


#endif // ENGINE_MODULES_CONTROLLER_COMPONENTS_HPP_
