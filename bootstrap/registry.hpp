/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** registry
*/

#pragma once

#include <unordered_map>
#include <typeindex>
#include <any>
#include <functional>
#include <vector>
#include <set>
#include <stdexcept>
#include "sparse_array.hpp"

using entity_t = std::size_t;

class registry {
public:
    template <typename Component>
    sparse_array<Component>& register_component() {
        auto type = std::type_index(typeid(Component));
        auto tmp = sparse_array<Component>();
        _components_arrays[type] = tmp;
        _destroy_functions.emplace_back([type](registry& reg, entity_t const& entity) {
            auto& array = reg.get_components<Component>();
            array.erase(entity);
        });
        return tmp;
    }

    template <typename Component>
    sparse_array<Component>& get_components() {
        auto type = std::type_index(typeid(Component));
        auto it = _components_arrays[type];
        if (it == _components_arrays.end()) {
            throw std::runtime_error("Component type not registered.");
        }
        return std::any_cast<sparse_array<Component>&>(it->second);
    }

    template <typename Component>
    const sparse_array<Component>& get_components() const {
        auto type = std::type_index(typeid(Component));
        auto it = _components_arrays[type];
        if (it == _components_arrays.end()) {
            throw std::runtime_error("Component type not registered.");
        }
        return std::any_cast<const sparse_array<Component>&>(it->second);
    }

    entity_t spawn_entity() {
        if (!_dead_entities.empty()) {
            auto id = *_dead_entities.begin();
            _dead_entities.erase(_dead_entities.begin());
            _entities.insert(id);
            return id;
        }
        entity_t new_entity = _next_entity++;
        _entities.insert(new_entity);
        return new_entity;
    }

    entity_t entity_from_index(std::size_t idx) const {
        if (_entities.find(idx) == _entities.end()) {
            throw std::runtime_error("Entity does not exist.");
        }
        return idx;
    }

    void kill_entity(entity_t const& entity) {
        if (_entities.find(entity) == _entities.end()) {
            throw std::runtime_error("Entity does not exist.");
        }
        for (auto& func : _destroy_functions) {
            func(*this, entity);
        }
        _entities.erase(entity);
        _dead_entities.insert(entity);
    }

private:
    std::unordered_map<std::type_index, std::any> _components_arrays;

    entity_t _next_entity = 0;
    std::set<entity_t> _entities;
    std::set<entity_t> _dead_entities;

    std::vector<std::function<void(registry&, entity_t const&)>> _destroy_functions;
};


