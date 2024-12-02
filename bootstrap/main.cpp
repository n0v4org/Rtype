/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** main
*/

#include "entity.hpp"

int main() {
    entity e1(42);

    size_t value = e1;
    std::cout << "Value: " << value << std::endl;

    if (e1 == entity(42)) {
        std::cout << "Entities are equal." << std::endl;
    }

    return 0;
}