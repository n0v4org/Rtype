/*
** EPITECH PROJECT, 2025
** r-type
** File description:
** Button
*/

#include "./include/Button.hpp"

namespace zef {
    namespace graph {

        Button::Button(const std::string& text,
                       const sf::Font& font,
                       const sf::Vector2f& position,
                       const sf::Vector2f& size,
                       sf::Color textColor,
                       sf::Color bgColor,
                       unsigned int charSize) {
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

        void Button::draw(sf::RenderTarget& target) {
            target.draw(_shape);
            target.draw(_text);
        }


        bool Button::isClicked(const sf::Vector2i& mousePos) const {
            sf::Vector2f mouseFloatPos(
                static_cast<float>(mousePos.x),
                static_cast<float>(mousePos.y)
            );
            return _shape.getGlobalBounds().contains(mouseFloatPos);
        }

        void Button::setBackgroundColor(const sf::Color& color) {
            _shape.setFillColor(color);
        }

        void Button::setTextColor(const sf::Color& color) {
            _text.setFillColor(color);
        }

        void Button::setPosition(const sf::Vector2f& position) {
            _shape.setPosition(position);
            
            sf::FloatRect bounds = _shape.getGlobalBounds();
            sf::FloatRect textBounds = _text.getLocalBounds();

            float textPosX = bounds.left + (bounds.width / 2.f) - (textBounds.width / 2.f);
            float textPosY = bounds.top  + (bounds.height / 2.f) - (textBounds.height / 1.4f);
            _text.setPosition(textPosX, textPosY);
        }

        sf::Vector2f Button::getPosition() const {
            return _shape.getPosition();
        }

        sf::Vector2f Button::getSize() const {
            return _shape.getSize();
        }

    } // namespace graph
} // namespace zef
