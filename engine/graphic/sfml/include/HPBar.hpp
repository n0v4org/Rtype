/*
** EPITECH PROJECT, 2025
** r-type
** File description:
** HPBar
*/

#ifndef HPBAR_HPP
#define HPBAR_HPP

#include <SFML/Graphics.hpp>

namespace zef {
    namespace graph {

        class HPBar {
        public:
            HPBar() = default;
            ~HPBar() = default;
            void draw(sf::RenderTarget& target,
              sf::RectangleShape& sharedRect,
              float posX, float posY,
              float width, float height,
              float value,
              sf::Color backgroundColor,
              sf::Color foregroundColor);
        };

    } // namespace graph
} // namespace zef

#endif // HPBAR_HPP
