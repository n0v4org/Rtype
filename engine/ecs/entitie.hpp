/*
** EPITECH PROJECT, 2024
** bootstrap
** File description:
** entitie
*/

#ifndef ENTITIE_HPP_
#define ENTITIE_HPP_

#include <cstddef>
#include "registry.hpp"

class registry;

class Entity {
    public:
        operator size_t() const {
            return _value;
        }

        friend class registry;

    private:
        explicit Entity(size_t val) : _value(val) {}
        size_t _value;
};


#endif /* !ENTITIE_HPP_ */
