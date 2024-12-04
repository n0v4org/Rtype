/*
** EPITECH PROJECT, 2024
** bootstrap
** File description:
** sparse_array
*/

#ifndef ENGINE_ECS_SPARSE_ARRAY_HPP_
#define ENGINE_ECS_SPARSE_ARRAY_HPP_

#include <optional>
#include <utility>
#include <vector>
#include <memory>
#include <iostream>

namespace ecs {
template <typename Component>
class sparse_array {
public:
  using value_type           = std::optional<Component>;
  using reference_type       = value_type &;
  using const_reference_type = value_type const &;
  using container_t          = std::vector<value_type>;
  using size_type            = typename container_t::size_type;
  using iterator             = typename container_t::iterator;
  using const_iterator       = typename container_t::const_iterator;

public:
  sparse_array() = default;
  sparse_array(sparse_array const &ohter) : _data(ohter._data) {
  }
  sparse_array(sparse_array &&other) noexcept : _data(std::move(other._data)) {
  }
  sparse_array(std::initializer_list<Component> list) {
    for (auto &item : list) {
      _data.push_back(value_type(item));
    }
  }
  ~sparse_array() = default;

  iterator begin() {
    return _data.begin();
  }
  const_iterator begin() const {
    return _data.begin();
  }
  const_iterator cbegin() const {
    return _data.cbegin();
  }

  iterator end() {
    return _data.end();
  }
  const_iterator end() const {
    return _data.end();
  }
  const_iterator cend() const {
    return _data.cend();
  }

  size_type size() const {
    return _data.size();
  }

  reference_type insert_at(size_type pos, Component const &component) {
    if (_data.size() <= pos) {
      _data.resize(pos + 1, std::nullopt);
    }
    _data[pos] = component;
    return _data[pos];
  }
  reference_type insert_at(size_type pos, Component &&component) {
    if (_data.size() <= pos) {
      _data.resize(pos + 1, std::nullopt);
    }
    _data[pos] = std::move(component);
    return _data[pos];
  }

  template <class... Params>
  reference_type emplace_at(size_type pos, Params &&...params) {
    if (_data.size() <= pos) {
      _data.resize(pos + 1, std::nullopt);
    }

    std::allocator<Component> allocator = _data.get_allocator();
    auto ptr                            = allocator.allocate(1);
    std::allocator_traits<std::allocator<Component>>::construct(
        allocator, ptr, std::forward<Params>(params)...);
    _data[pos] = value_type(*ptr);
    return _data[pos];
  }

  void erase(size_type pos) {
    if (pos < size())
      _data[pos] = std::nullopt;
  }

  size_type get_index(value_type const &component) const {
    for (size_type i = 0; i < size(); ++i) {
      if (component == _data[i].value())
        return i;
    }
    return -1;
  }

  sparse_array &operator=(sparse_array const &other) {
    _data = other.data;
    return *this;
  }
  sparse_array &operator=(sparse_array &&other) noexcept {
    _data = std::move(other._data);
    return *this;
  }
  reference_type operator[](size_t index) {
    return _data[index];
  }
  const_reference_type operator[](size_t index) const {
    return _data[index];
  }

  void display() const {
    if (!_data.empty()) {
      display_item(_data[0]);
      for (size_type i = 1; i < _data.size(); ++i) {
        std::cout << ", ";
        display_item(_data[i]);
      }
    }
    std::cout << std::endl;
  }

private:
  container_t _data;
  void display_item(value_type const &item) const {
    if (item == std::nullopt) {
      std::cout << "nullopt";
    } else {
      std::cout << item.value();
    }
  }
};
} //namespace ecs

#endif  // ENGINE_ECS_SPARSE_ARRAY_HPP_
