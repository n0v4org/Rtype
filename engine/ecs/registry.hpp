/*
** EPITECH PROJECT, 2024
** bootstrap
** File description:
** register
*/

#ifndef ENGINE_ECS_REGISTRY_HPP_
#define ENGINE_ECS_REGISTRY_HPP_

#include <unordered_map>
#include <map>
#include <typeindex>
#include <any>
#include <queue>
#include <functional>
#include <optional>
#include <utility>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
// #include <boost/type_index.hpp>

#include "entitie.hpp"
#include "zipper_iterator.hpp"
#include "zipper.hpp"
#include "indexed_zipper.hpp"
#include "sparse_array.hpp"

namespace zef {
  class Engine;
}  // namespace zef

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
        std::cout << "maxidquandspawn " << _maxId << "\n";
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
      std::cout << e << std::endl;
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
    void add_system(zef::Engine &engine, const std::string &moduleName,
                    Function &&f) {
      _systems[moduleName].push_back(
          [f = std::forward<Function>(f)](zef::Engine &e, ecs::registry &r) {
            f(e, r.get_components<Components>()...);
          });

      if (moduleName != "zefir" && _moduleThreads.find(moduleName) == _moduleThreads.end()) {
        _moduleNames.push_back(moduleName);
        _moduleExecutes[moduleName] = false;
        _moduleThreads[moduleName] = std::thread([this, moduleName, &engine]() {
          while (running) {
            std::unique_lock Glock(_mutex);
            std::unique_lock<std::mutex> lock(_moduleMutexes[moduleName]);
            _moduleCondVars[moduleName].wait(lock, [&]() {
              return _moduleExecutes[moduleName] || !running;
            });
            if (!running)
              break;
            for (auto &sys : _systems[moduleName]) {
              sys(engine, *this);
            }
            _moduleExecutes[moduleName] = false;
          }
        });
      }

      // if (_moduleThreads.find(moduleName) == _moduleThreads.end()) {
      //   _moduleThreads[moduleName] = std::thread([&systems =
      //   _systems[moduleName], &engine, &reg = *this, &mutex = _mutex](){
      //     while (1) {
      //       std::unique_lock lock(mutex);
      //       for (auto &sys : systems) {

      //         sys(engine, reg);
      //       }
      //     }
      //   });
      // }
    }

    void run_systems(zef::Engine &engine) {
      for (auto module : _moduleNames) {
        {
          std::lock_guard<std::mutex> lock(_moduleMutexes[module]);
          _moduleExecutes[module] = true;
        }
        _moduleCondVars[module].notify_one();
      }
      for (auto sys : _systems["zefir"]) {
        sys(engine, *this);
      }
    }

    size_t getEntityCount() {
      return _entityCount;
    }

    size_t getMaxId() {
      return _maxId;
    }

    void disp() {
      for (auto &&[k, v] : _components_arrays) {
        // std::type_index typeIndex = k;
        // auto boostTypeIndex = boost::typeindex::type_id_runtime(typeIndex);
        std::cout << "Nom lisible : " << k.name() << std::endl;
        // std::cout << typeIndex.name() << std::endl;
      }
    }

    template <typename... T>
    void register_with_str(size_t e, const std::string &name, T... args) {
      for (auto &&[k, v] : _components_arrays) {
        if (k.name() == name) {
        }
      }
    }

    std::queue<size_t> _unusedids;
    size_t _entityCount = 0;
    size_t _maxId = 0;
  private:
    std::unordered_map<std::type_index, std::any> _components_arrays;
    std::unordered_map<std::type_index,
                       std::function<void(registry &, entity_t const &)>>
        _deleteFunctions;

    std::map<std::string,
             std::vector<std::function<void(zef::Engine &, registry &)>>>
        _systems;
    std::map<std::string, std::thread> _moduleThreads;
    std::map<std::string, bool> _moduleExecutes;
    std::map<std::string, std::mutex> _moduleMutexes;
    std::map<std::string, std::condition_variable> _moduleCondVars;
    std::atomic<bool> running = std::atomic<bool>(true);
    std::mutex _mutex;
    std::vector<std::string> _moduleNames;

    // std::vector<std::function<void(zef::Engine &, registry &)>> _systems;
  };
}  // namespace ecs

#endif  // ENGINE_ECS_REGISTRY_HPP_
