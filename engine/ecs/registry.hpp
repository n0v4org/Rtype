/*
** EPITECH PROJECT, 2024
** bootstrap
** File description:
** register
*/

#ifndef ENGINE_ECS_REGISTRY_HPP_
#define ENGINE_ECS_REGISTRY_HPP_

#include <unordered_map>
#include <typeindex>
#include <any>
#include <queue>
#include <functional>
#include <optional>
#include <utility>
#include <vector>

#include "entitie.hpp"
#include "zipper_iterator.hpp"
#include "zipper.hpp"
#include "indexed_zipper.hpp"
#include "sparse_array.hpp"


namespace zef
{
  class Engine;
} // namespace zef

namespace ecs {
  class registry {
  public:
    using entity_t = Entity;

    registry()  = default;
    ~registry() = default;

    template <class Component>
    sparse_array<Component> &register_component() {
      _components_arrays[std::type_index(typeid(Component))] =
          sparse_array<Component>();
      _deleteFunctions[std::type_index(typeid(Component))] =
          [](registry &reg, entity_t const &entity) {
            reg.get_components<Component>().erase(entity);
          };
      return get_components<Component>();
    }

    template <class Component>
    sparse_array<Component> &get_components() {
      return std::any_cast<sparse_array<Component> &>(
          _components_arrays[std::type_index(typeid(Component))]);
    }

    template <class Component>
    sparse_array<Component> const &get_components() const {
      return std::any_cast<const sparse_array<Component> &>(
          _components_arrays.at(std::type_index(typeid(Component))));
    }

    template <class Component>
    std::optional<Component> &get_entity_component(size_t e) {
      return get_components<Component>()[e];
    }

    entity_t spawn_entity() {
      if (_unusedids.empty()) {
        _maxId++;
        return entity_t(_entityCount++);
      } else {
        entity_t entity(_unusedids.front());
        _unusedids.pop();
        _entityCount++;
        return entity;
      }
    }

    entity_t entity_from_index(std::size_t idx) {
      if (idx > _maxId) {
        throw std::runtime_error("entity_from_index: index too high.");
      }
      return entity_t(idx);
    }

    void kill_entity(entity_t const &e) {
      for (auto &func : _deleteFunctions) {
        func.second(*this, e);
      }
      _entityCount--;
      _unusedids.push(e);
    }

    template <typename Component>
    typename sparse_array<Component>::reference_type add_component(
        entity_t const &to, Component const &c) {
      return get_components<Component>().insert_at(to, c);
    }

    template <typename Component>
    typename sparse_array<Component>::reference_type add_component(
        entity_t const &to, Component &&c) {
      return get_components<Component>().insert_at(to, c);
    }

    template <typename Component, typename... Params>
    typename sparse_array<Component>::reference_type emplace_component(
        entity_t const &entity, Params &&...params) {
      return get_components<Component>().emplace_at(entity, params...);
    }

    template <typename Component>
    void remove_component(entity_t const &entity) {
      get_components<Component>().erase(entity);
    }

    template <class... Components, typename Function>
    void add_system(Function &&f) {
      this->_systems.push_back([f = std::forward<Function>(f)](zef::Engine& e, ecs::registry &r) {
          f(e, r.get_components<Components>()...);
      });
    }

    template <class... Components, typename Function>
    void new_add_system(Function &&f) {
      _systems.push_back([f = std::forward<Function>(f)](zef::Engine& e, registry &r) {
        for (auto a : zipper(r.get_components<Components>()...)) {
          f(e, std::get<Components &>(a)...);
        }
      });
    }

    //template <class... Components, typename Function>
    //void add_system(Function const &f) {
    //  _systems.push_back([](registry &r, Function const &f) {
    //    for (auto a : zipper(r.get_components<Components>()...)) {
    //      f(std::get<Components &>(a)...);
    //    }
    //  });
    //}

    void run_systems(zef::Engine& engine) {
      for (auto &system : _systems) {
        system(engine, *this);
      }
    }

  private:
    size_t _entityCount = 0;
    std::unordered_map<std::type_index, std::any> _components_arrays;
    std::unordered_map<std::type_index,
                       std::function<void(registry &, entity_t const &)>>
        _deleteFunctions;
    size_t _maxId       = 0;
    std::vector<std::function<void(zef::Engine&, registry &)>> _systems;
    std::queue<size_t> _unusedids;
  };
}  // namespace ecs

#endif  // ENGINE_ECS_REGISTRY_HPP_
