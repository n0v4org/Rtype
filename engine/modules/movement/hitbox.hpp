/*
** EPITECH PROJECT, 2024
** leVraiRtype
** File description:
** hitbox
*/

#ifndef ENGINE_MODULES_COLLISION_HITBOX_HPP_
#define ENGINE_MODULES_COLLISION_HITBOX_HPP_

#include <cmath>

namespace zef {
    namespace utils {
    class hitbox {
        enum type {
            RECT,
            CIRCLE
        };
        public:
            // Rectangle constructor (position will be the center of the rectangle)
            hitbox(float offsetX, float offsetY, float width, float height):
                _offsetX(offsetX), _offsetY(offsetY), _posX(0), _posY(0), _height(height), _width(width), _type(RECT) {}
            // Cirlce constructor
            hitbox(float offsetX, float offsetY, float radius):
                _offsetX(offsetX), _offsetY(offsetY), _posX(0), _posY(0), _radius(radius), _type(CIRCLE) {}
            // Destructor
            ~hitbox() = default;

            // Check if another hitbox is colliding
            bool isColliding(const hitbox &other) {
                bool collide = false;
                if (_type == CIRCLE && other._type == CIRCLE) {
                    float dist = sqrt(pow(_posX - other._posX, 2) + pow(_posY - other._posY, 2));
                    collide = dist < (_radius + other._radius);
                } else if (_type == CIRCLE && other._type == RECT) {
                    float closestX = std::max(other._posX, std::min(_posX, other._posX + other._width));
                    float closestY = std::max(other._posY, std::min(_posY, other._posY + other._height));
                    float sqDistance = pow(closestX - _posX, 2) + pow(closestY - _posY, 2);
                    collide = sqDistance < pow(_radius, 2);
                } else if (_type == RECT && other._type == CIRCLE) {
                    float closestX = std::max(_posX, std::min(other._posX, _posX + _width));
                    float closestY = std::max(_posY, std::min(other._posY, _posY + _height));
                    float sqDistance = pow(closestX - other._posX, 2) + pow(closestY - other._posY, 2);
                    collide = sqDistance < pow(other._radius, 2);
                } else {
                    collide = !((_posX + _width <= other._posX)
                            ||  (other._posX + other._width <= _posX)
                            ||  (_posY + _height <= other._posY)
                            ||  (other._posY + other._height <= _posY));
                }
                return collide;
            }
        
            float _offsetX;
            float _offsetY;
            float _posX;
            float _posY;
            float _height;
            float _width;
            float _radius;
            type _type;
    };
    } // namespace utils
}

#endif // ENGINE_MODULES_COLLISION_HITBOX_HPP_
