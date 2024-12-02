/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** entity
*/

#pragma once

#include <iostream>

class entity {
private:

    size_t value_;

public:

    explicit entity(size_t value) : value_(value) {}
    operator size_t() const {
        return value_;
    }
    ~entity() {}

};

