/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** sparse_array
*/

#pragma once

#include <optional>
#include <vector>
#include <memory>

template <typename Component>
class sparse_array {
public:
    using value_type = std::optional<Component>;
    using reference_type = value_type&;
    using const_reference_type = value_type const&;
    using container_t = std::vector<value_type>;
    using size_type = typename container_t::size_type;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

public:
    sparse_array(){}
    sparse_array(sparse_array const&){}
    sparse_array(sparse_array&&) noexcept{}
    ~sparse_array(){}
    sparse_array& operator=(sparse_array const&);
    sparse_array& operator=(sparse_array&&) noexcept;
    reference_type operator[](size_t idx);
    const_reference_type operator[](size_t idx) const;
    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;
    size_type size() const;

    reference_type insert_at(size_type pos, Component const& component) {
        if (pos >= _data.size()) {
            _data.resize(pos + 1);
        }
        _data.at(pos) = component;
        return _data.at(pos);
    }

    reference_type insert_at(size_type pos, Component&& component) {
        if (pos >= _data.size()) {
            _data.resize(pos + 1);
        }
        _data.at(pos) = std::move(component);
        return _data.at(pos);
    }

    template <class... Params>

    reference_type emplace_at(size_type pos, Params&&... params) {
        if (pos >= _data.size()) {
            _data.resize(pos + 1);
        }
        std::allocator<Component> t = _data.get_allocator();
        auto p = t.allocate(1);
        std::allocator_traits<std::allocator<Component>>::construct(t, p, params...);
        value_type a(*p);
        _data.at(pos) = a;
        return _data.at(pos);
    }

    void erase(size_type pos) {
        if (pos < _data.size()) {
            _data[pos] = std::nullopt;
        }
    }

    size_type get_index(value_type const& component) const {
        for (size_type i = 0; i < _data.size(); ++i) {
            if (_data.at(i) == component) {
                return i;
            }
        }
        throw std::out_of_range("Component not found in sparse_array.");
    }

    void display() const {
        for (size_type i = 0; i < _data.size(); ++i) {
            if (_data[i]) {
                std::cout << "Index " << i << ": " << *_data[i] << "\n";
            } else {
                std::cout << "Index " << i << ": empty\n";
            }
        }
    }

private:
    container_t _data;
};
