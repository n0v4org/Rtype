/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** Engine
*/

#include "Engine.hpp"

namespace zef {

  namespace sys {
    void resolveEvent(Engine& engine,
                      ecs::sparse_array<comp::event_listener>& evtls) {
      while (!engine._events.empty()) {
        Event evt = engine._events.front();
        if (engine.reg.get_components<comp::event_listener>().size() >
                evt.entity &&
            engine.reg.get_entity_component<comp::event_listener>(
                evt.entity)) {  // handle error when the entity dont handle the
                                // event
          if (engine.reg.get_entity_component<comp::event_listener>(evt.entity)
                  ->_functions.find(evt.tid) !=
              engine.reg.get_entity_component<comp::event_listener>(evt.entity)
                  ->_functions.end())
            engine.reg.get_entity_component<comp::event_listener>(evt.entity)
                ->_functions[evt.tid](engine, evt.entity, evt);
        }
        engine._events.pop();
      }
    }

    void nresolveEvent(Engine& engine,
                       ecs::sparse_array<comp::new_event_listener>& evtls) {
      while (!engine._nevents.empty()) {
        newEvent evt = engine._nevents.front();

        for (auto&& [i, listener] : ecs::indexed_zipper(evtls)) {
          if (i == evt.entity) {
            listener.execute(evt.name, engine, i, evt.tpl);
          }
        }

        engine._nevents.pop();
      }
    }
  }  // namespace sys
}  // namespace zef