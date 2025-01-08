/*

** EPITECH PROJECT, 2024
** RTYPE
** File description:
** events
*/

#ifndef ENGINE_EVENTS_HPP_
#define ENGINE_EVENTS_HPP_

#include <map>
#include <any>
#include <typeindex>
#include <functional>
#include "./ecs/sparse_array.hpp"

namespace zef {
  class Engine;

  class Event {
  public:
    size_t entity;

    std::any tpl;
    std::type_index tid = typeid(int);

    template <typename T>
    T to_struct(std::function<void(Engine&, size_t, T)> f) {
      return std::any_cast<T>(tpl);
    }
  };

  class newEvent {
  public:
    size_t entity;

    std::any tpl;
    std::string name;

    //template <typename T>
    //T to_struct(std::function<void(Engine&, size_t, T)> f) {
    //  return std::any_cast<T>(tpl);
    //}
  };

  namespace comp {

    struct new_event_listener {
      public:
        new_event_listener() {}

        template <typename ...U, typename Functor>
        void setEvent(std::string name, Functor&& f) {
          _setEvent<U...>(name, f, std::index_sequence_for<U...>{});
        }

        template <typename ...U, typename Functor, std::size_t... Indices>
        void _setEvent(std::string name, Functor&& f, std::index_sequence<Indices...>) {
          _map[name] = [&] (zef::Engine& engine, size_t e, std::any tpl) {
            auto tmpt = std::any_cast<std::tuple<U...>>(tpl);
            f(engine, e, std::get<Indices>(tmpt)...);
          };
        }


        void execute(std::string name, zef::Engine& engine, size_t e, std::any tpl) {
          _map[name](engine, e, tpl);
        }


        std::map<std::string, std::function<void(zef::Engine&, size_t, std::any)>> _map;
    };

    struct event_listener {
    public:
      event_listener() {
      }

      template <typename... T>
      static event_listener construct(
          std::function<void(Engine&, size_t, T)>... funcs) {
        event_listener new_event_handler;
        ((new_event_handler.setEvent<T>(funcs)), ...);
        return new_event_handler;
      }

      template <typename T>
      void setEvent(std::function<void(Engine&, size_t, T)> f) {
        _functions[std::type_index(typeid(T))] = [f](Engine& engine,
                                                     size_t self, Event event) {
          T str = event.to_struct<T>(f);
          f(engine, self, str);
        };
      }

      std::map<std::type_index,
               std::function<void(Engine&, size_t, Event event)>>
          _functions;
    };
  }  // namespace comp
}  // namespace zef

#endif  // ENGINE_EVENTS_HPP_
