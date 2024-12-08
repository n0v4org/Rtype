/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** zipper_iterator
*/

#ifndef ENGINE_ECS_ZIPPER_ITERATOR_HPP_
#define ENGINE_ECS_ZIPPER_ITERATOR_HPP_

#include <tuple>
#include <optional>
#include <iterator>
#include <cstddef>

namespace ecs {
  template <class... Containers>
  class zipper_iterator {
    template <class Container>
    using iterator_t = decltype(std::declval<Container>().begin());

    template <class Container>
    using it_reference_t = typename iterator_t<Container>::reference;

  public:
    using value_type = std::tuple<
        decltype(std::declval<it_reference_t<Containers>>().value())&...>;
    using reference         = value_type;
    using pointer           = void;
    using difference_type   = std::size_t;
    using iterator_category = std::input_iterator_tag;
    using iterator_tuple    = std::tuple<iterator_t<Containers>...>;

    // Friend declaration for zipper
    template <class... Cs>
    friend class zipper;

    // Constructor
    zipper_iterator(iterator_tuple const& it_tuple, std::size_t max) {
      _max     = max;
      _current = it_tuple;
      _idx     = 0;
      if (!all_set(_seq))
        incr_all(_seq);
    }

  public:
    // Copy constructor
    zipper_iterator(zipper_iterator const& z) {
      _current = z._current;
      _max     = z._max;
      _idx     = z._idx;
      //_seq = z._seq;
    }

    // Post-increment
    zipper_iterator operator++(int) {
      zipper_iterator tmp = *this;
      incr_all(_seq);
      return tmp;
    }

    // Pre-increment
    zipper_iterator& operator++() {
      incr_all(_seq);
      // std::cout << "it idx: " << _idx << std::endl;
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
    friend bool operator==(zipper_iterator const& lhs,
                           zipper_iterator const& rhs) {
      return (lhs._idx == rhs._idx);
    }

    // Inequality comparison
    friend bool operator!=(zipper_iterator const& lhs,
                           zipper_iterator const& rhs) {
      return !(lhs == rhs);
    }

    std::size_t _idx;

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
      return (... && (*std::get<Is>(_current)).has_value());
    }

    // Return a tuple of references to components
    template <std::size_t... Is>
    value_type to_value(std::index_sequence<Is...>) {
      return std::tie((*std::get<Is>(_current)).value()...);
    }

  private:
    iterator_tuple _current;
    std::size_t _max;  // Prevent infinite loop by comparing to _idx
    static constexpr std::index_sequence_for<Containers...> _seq{};
  };
}  // namespace ecs

#endif  // ENGINE_ECS_ZIPPER_ITERATOR_HPP_