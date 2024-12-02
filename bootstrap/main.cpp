/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** main
*/

#include "entity.hpp"
#include "sparse_array.hpp"

int main() {
    sparse_array<int> sa;

    sa.insert_at(0, 42);
    sa.insert_at(3, 100);
    sa.insert_at(1, 50);
    std::cout << "After insert_at:\n";
    sa.display();

    sa.emplace_at(2, 75);
    std::cout << "\nAfter emplace_at:\n";
    sa.display();

    sa.erase(1);
    std::cout << "\nAfter erase at index 1:\n";
    sa.display();

    try {
        size_t index = sa.get_index(100);
        std::cout << "\nIndex of component 100: " << index << "\n";
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << "\n";
    }

    try {
        size_t index = sa.get_index(999);
        std::cout << "Index of component 999: " << index << "\n";
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << "\n";
    }

    return 0;
}