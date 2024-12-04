/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** events
*/

#ifndef ENGINE_ECS_EVENTS_HPP_
#define ENGINE_ECS_EVENTS_HPP_

#include <map>

class Engine;
class Event {
    public:
        size_t entity;

        std::any tpl;
        std::type_index tid = typeid(int);

        template<typename T>
        T to_struct(std::function<void(Engine&, size_t, T)> f) {
            return std::any_cast<T>(tpl);
        }
};

struct event_handler_c {
    public:
        template <typename T>
        void setEvent(std::function<void(Engine&, size_t, T)> f) {
            _functions[std::type_index(typeid(T))] = [f](Engine& engine, size_t self, Event event) {
                T str =  event.to_struct<T>(f);
                f(engine, self, str);
            };
        }

        std::map<std::type_index, std::function<void(Engine&, size_t, Event event)>> _functions;

};

#endif // ENGINE_ECS_EVENTS_HPP_
