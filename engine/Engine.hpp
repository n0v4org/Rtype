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


#include "graphic/sfml/Sfml.hpp"


#include "graphic/IDisplayModule.hpp"
#include "graphic/ADisplayModule.hpp"

#include "ecs/registry.hpp"
#include "Events.hpp"
#include "utils/inputsUtils.hpp"




namespace zef {

  namespace sys
  {
    void resolveEvent(Engine& engine, ecs::sparse_array<comp::event_listener>& evtls);
  } // namespace sys

  class Engine {
  public:

    Engine() {
      clock = std::chrono::high_resolution_clock::now();
    }
    ecs::registry reg;

    friend void sys::resolveEvent(Engine& engine, ecs::sparse_array<comp::event_listener>& evtls);

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
    void registerComponent() {
      reg.register_component<Component>();
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


    template <class... Components, typename Function>
    void addSystem(Function &&f) {
      reg.add_system<Components...>(f);
    }

    template <typename Patron, typename ...T>
    ecs::Entity instanciatePatron(T... args) {
      ecs::Entity new_entity = reg.spawn_entity();
      Patron::instanciate(*this, new_entity, args...);
      return new_entity;
    }

    void updateUserInputs() {
      _user_inputs.keyboard._released.clear();
      _user_inputs.keyboard._pressed.clear();
      _user_inputs.mouse._pressed.clear();
      _user_inputs.mouse._released.clear();
      GraphLib->updateUserInputs(_user_inputs);
    }

    const utils::UserInputs& getUserInputs() {
      return _user_inputs;
    }



    void initGraphLib(const std::string& assetFolder, const std::string& windowName) {
      GraphLib.reset(graph::entryPoint());
      GraphLib->initialize(assetFolder);
    }



    void run() {
      clock = std::chrono::high_resolution_clock::now();
      while (true) {
        elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - clock);
        clock = std::chrono::high_resolution_clock::now();
        

        
        if (GraphLib)
          GraphLib->clear();

        reg.run_systems(*this);

        if (GraphLib)
          GraphLib->refresh();

      }
    }


    std::unique_ptr<zef::graph::IDisplayModule> GraphLib;
    std::chrono::high_resolution_clock::time_point clock;// = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds elapsed;

  private:
    int gameFps = 60;

    utils::UserInputs _user_inputs;
    std::queue<Event> _events;
  };



  namespace sys
  {
    void resolveEvent(Engine& engine, ecs::sparse_array<comp::event_listener>& evtls) {
      while (!engine._events.empty()) {
        Event evt = engine._events.front();
        if (engine.reg.get_components<comp::event_listener>().size() > evt.entity && engine.reg.get_entity_component<comp::event_listener>(
                evt.entity)) {  // handle error when the entity dont handle the
                                // event
          if (engine.reg.get_entity_component<comp::event_listener>(evt.entity)->_functions.find(evt.tid)
          != engine.reg.get_entity_component<comp::event_listener>(evt.entity)->_functions.end())
            engine.reg.get_entity_component<comp::event_listener>(evt.entity)
                ->_functions[evt.tid](engine, evt.entity, evt);
        }
        engine._events.pop();
      }
    }
  } // namespace sys
}  // namespace zef

#endif  // ENGINE_ENGINE_HPP_
