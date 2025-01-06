/*
** EPITECH PROJECT, 2025
** r-type
** File description:
** Button
*/

#include "Button.hpp"

namespace zef {
    namespace graph {

        Button::Button(const std::string& text,
                       const sf::Font& font,
                       const sf::Vector2f& position,
                       const sf::Vector2f& size,
                       sf::Color textColor,
                       sf::Color bgColor,
                       unsigned int charSize)
        {
            _shape.setPosition(position);
            _shape.setSize(size);
            _shape.setFillColor(bgColor);

            _text.setString(text);
            _text.setFont(font);
            _text.setCharacterSize(charSize);
            _text.setFillColor(textColor);

            sf::FloatRect textBounds = _text.getLocalBounds();
            float textPosX = position.x + (size.x / 2.f) - (textBounds.width / 2.f);
            float textPosY = position.y + (size.y / 2.f) - (textBounds.height / 1.4f);
            _text.setPosition(textPosX, textPosY);
        }

        void Button::draw(sf::RenderTarget& target)
        {
        }

        bool Button::isClicked(const sf::Vector2i& mousePos) const
        {
            return false;
        }

        void Button::setBackgroundColor(const sf::Color& color)
        {
        }

        void Button::setTextColor(const sf::Color& color)
        {
        }

        void Button::setPosition(const sf::Vector2f& position)
        {
        }

        sf::Vector2f Button::getPosition() const
        {
            return {};
        }

        sf::Vector2f Button::getSize() const
        {
            return {};
        }

    } // namespace graph
} // namespace zef
