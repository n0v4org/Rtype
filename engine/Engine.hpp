/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** Engine
*/

#ifndef ENGINE_ENGINE_HPP_
#define ENGINE_ENGINE_HPP_

#include <map>
#include <memory>
#include <queue>

#include "ecs/registry.hpp"
#include "events.hpp"

namespace zef {
  class Engine {
  public:
    ecs::registry reg;

    template <typename T, typename... U>
    void sendEvent(size_t entity, U... args) {
      Event evt;
      evt.entity = entity;
      evt.tpl    = (T){args...};
      evt.tid    = std::type_index(typeid(T));
      _events.push(evt);
    }

    void resolveEvent() {
      while (!_events.empty()) {
        Event evt = _events.front();
        if (reg.get_entity_component<event_handler_c>(
                evt.entity)) {  // handle error when the entity dont handle the
                                // event
          reg.get_entity_component<event_handler_c>(evt.entity)
              ->_functions[evt.tid](*this, evt.entity, evt);
        }
        _events.pop();
      }
    }

    template <typename Component>
    Component& fetchEntityComponent(size_t e) {
      std::optional<Component>& optComp = reg.get_components<Component>()[e];
      if (optComp == std::nullopt)
        throw std::runtime_error("amjfeazlja\n");
      return optComp.value();
    }

  private:
    std::queue<Event> _events;
  };
}  // namespace zef

#endif  // ENGINE_ENGINE_HPP_
