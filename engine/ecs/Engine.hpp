/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** Engine
*/

#ifndef ENGINE_ECS_ENGINE_HPP_
#define ENGINE_ECS_ENGINE_HPP_

#include "ecs.hpp"
#include "events.hpp"
#include <map>
#include <memory>
#include <queue>


class Engine {
    public:
        registry reg;

        template <typename T, typename ...U>
        void sendEvent(size_t entity, U ...args) {
            Event evt;
            evt.entity = entity;
            evt.tpl = (T){args...};
            evt.tid = std::type_index(typeid(T));
            _events.push(evt);
        }

        void resolveEvent() {
            while (!_events.empty()) {
                Event evt = _events.front();
                if (reg.get_entity_component<event_handler_c>(evt.entity)) {  //handle error when the entity dont handle the event
                    reg.get_entity_component<event_handler_c>(evt.entity)->_functions[evt.tid](*this, evt.entity, evt);
                }
                _events.pop();
            }
        }

    private:
        std::queue<Event> _events;


};



#endif // ENGINE_ECS_ENGINE_HPP_
