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

        HPBar::HPBar(const sf::Vector2f& position,
                     const sf::Vector2f& size,
                     float initialValue,
                     const sf::Color& backgroundColor,
                     const sf::Color& foregroundColor) {
                        _background.setPosition(position);
                        _background.setSize(size);
                        _background.setFillColor(backgroundColor);

                        _foreground.setPosition(position);
                        _foreground.setSize(size);
                        _foreground.setFillColor(foregroundColor);
                    
                        _value = std::clamp(_value, 0.f, 100.f);

                        updateForeground();
        }

        void HPBar::setValue(float newValue) {
            _value = std::clamp(newValue, 0.f, 100.f);
            updateForeground();
        }

        void HPBar::draw(sf::RenderTarget& target) {
        }

        void HPBar::setPosition(const sf::Vector2f& position) {
            _background.setPosition(position);
            _foreground.setPosition(position);
            updateForeground();
        }

        void HPBar::setSize(const sf::Vector2f& size) {
            _background.setSize(size);
            updateForeground();
        }

        void HPBar::updateForeground() {
            sf::Vector2f bgSize = _background.getSize();
            float width = bgSize.x * (_value / 100.f);
            float height = bgSize.y;

            _foreground.setSize({width, height});
        }
    } // namespace graph
} // namespace zef
