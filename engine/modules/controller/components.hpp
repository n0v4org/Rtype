/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** controllable
*/

#ifndef ENGINE_COMPONENTS_CONTROLLABLE_HPP_
#define ENGINE_COMPONENTS_CONTROLLABLE_HPP_


#include <map>
#include <functional>
#include "../../Engine.hpp"

namespace zef {

    namespace comp
    {
        class controllable {
            public:
                controllable(){}

                template <typename Events, typename ...T>
                void bindOnPressed(zef::Keys key, T ...args) {
                    _pressed[key] = [args...](Engine& engine, size_t entity){
                        engine.sendEvent<Events>(entity, args...);
                    };
                }

                template <typename Events, typename ...T>
                void bindOnRelease(zef::Keys key, T ...args) {
                    _released[key] = [args...](Engine& engine, size_t entity){
                        engine.sendEvent<Events>(entity, args...);
                    };
                }

                std::map<zef::Keys, std::function<void(Engine &, size_t)>> _pressed;
                std::map<zef::Keys, std::function<void(Engine &, size_t)>> _released;
        };
    } // namespace comp
} // namespace zef


#endif // ENGINE_COMPONENTS_CONTROLLABLE_HPP_
