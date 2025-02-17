/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** indexed_zipper
*/

#ifndef ENGINE_ECS_INDEXED_ZIPPER_HPP_
#define ENGINE_ECS_INDEXED_ZIPPER_HPP_

#include <tuple>
#include <optional>
#include <iterator>
#include <cstddef>

namespace ecs {
  template <class... Containers>
  class indexed_zipper_iterator {
    template <class Container>
    using iterator_t = decltype(std::declval<Container>().begin());

    template <class Container>
    using it_reference_t = typename iterator_t<Container>::reference;

  public:
    using value_type =
        std::tuple<size_t, decltype(std::declval<it_reference_t<Containers>>()
                                        .value())&...>;
    using reference         = value_type;
    using pointer           = void;
    using difference_type   = std::size_t;
    using iterator_category = std::input_iterator_tag;
    using iterator_tuple    = std::tuple<iterator_t<Containers>...>;

    // Friend declaration for zipper
    template <class... Cs>
    friend class zipper;

    // Constructor
    indexed_zipper_iterator(iterator_tuple const& it_tuple,
                            iterator_tuple const& it_end, std::size_t max,
                            size_t idx = 0) {
      _max     = max;
      _current = it_tuple;
      _idx     = idx;
      _end     = it_end;
      if (_idx < _max && !all_set(_seq)) {
        incr_all(_seq);
      }
    }

  public:
    // Copy constructor
    indexed_zipper_iterator(indexed_zipper_iterator const& z) {
      _current = z._current;
      _max     = z._max;
      _idx     = z._idx;
      _end     = z._end;
      //_seq = z._seq;
    }

    // Post-increment
    indexed_zipper_iterator operator++(int) {
      indexed_zipper_iterator tmp = *this;
      incr_all(_seq);
      return tmp;
    }

    // Pre-increment
    indexed_zipper_iterator& operator++() {
      incr_all(_seq);
      return *this;
    }

    // Dereference
    value_type operator*() {
      return to_value(_seq);
    }

    // Arrow operator
    value_type operator->() {
      return to_value(_seq);
    }

    // Equality comparison
    friend bool operator==(indexed_zipper_iterator const& lhs,
                           indexed_zipper_iterator const& rhs) {
      return lhs._idx == rhs._idx;
    }

    // Inequality comparison
    friend bool operator!=(indexed_zipper_iterator const& lhs,
                           indexed_zipper_iterator const& rhs) {
      return !(lhs == rhs);
    }

  private:
    // Increment every iterator
    template <std::size_t... Is>
    void incr_all(std::index_sequence<Is...>) {
      while (_idx < _max) {
        _idx++;
        (..., (std::get<Is>(_current)++));
        if (all_set(_seq))
          break;
      }
    }

    // Check if every std::optional is set
    template <std::size_t... Is>
    bool all_set(std::index_sequence<Is...>) {
      bool ret = ((std::get<Is>(_current) != std::get<Is>(_end) &&
                   (*std::get<Is>(_current)).has_value()) &&
                  ...);
      return ret;
    }

    // Return a tuple of references to components
    template <std::size_t... Is>
    value_type to_value(std::index_sequence<Is...>) {
      return std::tie(_idx, (*std::get<Is>(_current)).value()...);
    }

  public:
    std::size_t _idx;

  private:
    iterator_tuple _current;
    iterator_tuple _end;
    std::size_t _max;  // Prevent infinite loop by comparing to _idx
    static constexpr std::index_sequence_for<Containers...> _seq{};
  };

  template <class... Containers>
  class indexed_zipper {
  public:
    using iterator       = indexed_zipper_iterator<Containers...>;
    using iterator_tuple = typename iterator::iterator_tuple;

    explicit indexed_zipper(Containers&... cs)
      : _begin(std::make_tuple(cs.begin()...))
      , _end(_compute_end(cs...))
      , _size(_compute_size(cs...)) {
    }

    iterator begin() {
      if (_size == 0)
        return iterator(_end, _end, _size);
      return iterator(_begin, _end, _size);
    }

    iterator end() {
      auto it = iterator(_end, _end, _size, _size);
      // it._idx = _size;
      return it;
    }

  private:
    static iterator_tuple _compute_end(Containers&... containers) {
      size_t size = _compute_size(containers...);

      auto ret = std::make_tuple(/*size - 1,*/ ([&] {
        auto iterator = containers.begin();
        for (size_t i = 0; i < size; ++i) {
          iterator++;
        }
        return iterator;
      }())...);
      return ret;
    }

    static size_t _compute_size(Containers&... containers) {
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

    iterator_tuple _begin;
    iterator_tuple _end;
    std::size_t _idx = 0;
    std::size_t _size;
  };
}  // namespace ecs

#endif  // ENGINE_ECS_INDEXED_ZIPPER_HPP_
