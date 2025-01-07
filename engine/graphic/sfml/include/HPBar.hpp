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
            HPBar(const sf::Vector2f& position,
                  const sf::Vector2f& size,
                  float initialValue,
                  const sf::Color& backgroundColor = sf::Color::Red,
                  const sf::Color& foregroundColor = sf::Color::Green);
            void setValue(float newValue);
            void draw(sf::RenderTarget& target);
            void setPosition(const sf::Vector2f& position);
            void setSize(const sf::Vector2f& size);
        private:
            sf::RectangleShape _background;
            sf::RectangleShape _foreground;
            float _value;
            void updateForeground();
        };
    } // namespace graph
} // namespace zef

#endif // HPBAR_HPP