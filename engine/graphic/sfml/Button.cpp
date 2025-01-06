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
