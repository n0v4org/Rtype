/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** zipper
*/

#ifndef ENGINE_ECS_ZIPPER_HPP_
#define ENGINE_ECS_ZIPPER_HPP_

#include <functional>
#include <iostream>

#include "zipper_iterator.hpp"

template <typename T>
void PrintType(T &&) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

template <class... Containers>
class zipper {
public:
  using iterator       = zipper_iterator<Containers...>;
  using iterator_tuple = typename iterator::iterator_tuple;

  explicit zipper(Containers &...cs)
    : _begin(cs.begin()...)
    , _end(_compute_end(cs...))
    , _size(_compute_size(cs...)) {
  }

  iterator begin() {
    return iterator(_begin, _size);
  }
  iterator end() {
    auto it = iterator(_end, _size);
    it._idx = _size;
    return it;
  }

private:
  // Helper function to determine the maximum index of our iterators.
  static size_t _compute_size(Containers &...containers) {
    size_t size = 0;
    bool init   = false;

    (
        [&] {
          if (init) {
            size = (size < containers.size()) ? (size) : (containers.size());
          } else {
            init = true;
            size = containers.size();
          }
        }(),
        ...);
    return size;
  }

  // Helper function to compute an iterator_tuple that will allow us to
  // build our end iterator.
  static iterator_tuple _compute_end(Containers &...containers) {
    size_t size = _compute_size(containers...);

    auto ret = std::make_tuple(([&] {
      auto iterator = containers.begin();
      size_t i;
      for (i = 0; i < size; ++i) {
        iterator++;
      }
      return iterator;
    }())...);
    return ret;
  }

private:
  iterator_tuple _begin;
  iterator_tuple _end;
  size_t _size;
};

#endif  // ENGINE_ECS_ZIPPER_HPP_
