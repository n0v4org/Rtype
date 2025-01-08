/*
** EPITECH PROJECT, 2025
** r-type
** File description:
** HPBar
*/

#include "HPBar.hpp"
#include <algorithm>

namespace zef {
    namespace graph {

        void HPBar::draw(sf::RenderTarget& target,
                         sf::RectangleShape& sharedRect,
                         float posX, float posY,
                         float width, float height,
                         float value,
                         sf::Color backgroundColor,
                         sf::Color foregroundColor) {

            value = std::clamp(value, 0.f, 1.f);

            sharedRect.setPosition({posX, posY});
            sharedRect.setSize({width, height});
            sharedRect.setFillColor(backgroundColor);

            target.draw(sharedRect);

            float fillWidth = (width * value) / 1.f;
            sharedRect.setSize({fillWidth, height});
            sharedRect.setFillColor(foregroundColor);

            target.draw(sharedRect);
        }

    } // namespace graph
} // namespace zef
