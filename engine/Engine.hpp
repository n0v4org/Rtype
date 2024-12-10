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
#include "Events.hpp"
#include "modules/controller/InputsController.hpp"

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
        if (reg.get_components<comp::event_listener>().size() > evt.entity && reg.get_entity_component<comp::event_listener>(
                evt.entity)) {  // handle error when the entity dont handle the
                                // event
          if (reg.get_entity_component<comp::event_listener>(evt.entity)->_functions.find(evt.tid)
          != reg.get_entity_component<comp::event_listener>(evt.entity)->_functions.end())
            reg.get_entity_component<comp::event_listener>(evt.entity)
                ->_functions[evt.tid](*this, evt.entity, evt);
        }
        _events.pop();
      }
    }

    template <typename Component>
    Component& fetchEntityComponent(size_t e) {
      std::optional<Component>& optComp = reg.get_components<Component>()[e];
      if (optComp == std::nullopt)
        throw std::runtime_error("this entity does not have the component");
      return optComp.value();
    }

    template <typename Component>
    void addEntityComponent(ecs::Entity e, Component&& c) {
      reg.add_component<Component>(e, c);
    }

    template <typename Component>
    void addEntityComponent(ecs::Entity const& e, Component const& c) {
      reg.add_component<Component>(e, c);
    }

    template <typename Component, typename ...T>
    void addEntityComponent(ecs::Entity const& e, T ...args) {
      reg.emplace_component<Component>(e, args...);
    }

    template <typename Component>
    void removeEntityComponent(ecs::Entity const& e) {
      reg.remove_component<Component>(e);
    }

    template <typename Patron, typename ...T>
    ecs::Entity instanciatePatron(T... args) {
      ecs::Entity new_entity = reg.spawn_entity();
      Patron::instanciate(*this, new_entity, args...);
      return new_entity;
    }



    UserInputs getUserInputs() {
      UserInputs user_inputs;

      user_inputs.mouse.x = 90;
      user_inputs.mouse.y = 34;

      user_inputs.keyboard.PressedKeys.push_back(zef::A);

      return user_inputs;
    }

  private:
    std::queue<Event> _events;
  };
}  // namespace zef

#endif  // ENGINE_ENGINE_HPP_
