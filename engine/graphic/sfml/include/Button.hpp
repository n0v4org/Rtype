/*
** EPITECH PROJECT, 2025
** r-type
** File description:
** Button
*/

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>

namespace zef {
    namespace graph {

        class Button {
        public:
            Button(const std::string& text,
                   const sf::Font& font,
                   const sf::Vector2f& position,
                   const sf::Vector2f& size,
                   sf::Color textColor = sf::Color::White,
                   sf::Color bgColor   = sf::Color::Red,
                   unsigned int charSize = 24);

            void draw(sf::RenderTarget& target);
            bool isClicked(const sf::Vector2i& mousePos) const;
            void setBackgroundColor(const sf::Color& color);
            void setTextColor(const sf::Color& color);
            void setPosition(const sf::Vector2f& position);
            sf::Vector2f getPosition() const;
            sf::Vector2f getSize() const;

        private:
            sf::RectangleShape _shape;
            sf::Text           _text;
        };

    } // namespace graph
} // namespace zef

#endif // BUTTON_HPP
