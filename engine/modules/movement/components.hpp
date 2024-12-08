/*
** EPITECH PROJECT, 2024
** leVraiRtype
** File description:
** collision
*/

#ifndef ENGINE_MODULES_COLLISION_COMPONENTS_HPP_
#define ENGINE_MODULES_COLLISION_COMPONENTS_HPP_

#include <vector>
#include "hitbox.hpp"

namespace zef {
    namespace comp {
        class position {
            public:
                position(float posX, float posY): x(posX), y(posY) {}
                ~position() = default;

                float x;
                float y;
        };
        class vector {
            public:
                vector(float posX, float posY): x(posX), y(posY) {}
                ~vector() = default;

                float x;
                float y;
        };

        class collidable {
            
            public:
                // Collidable constructor
                collidable(std::vector<utils::hitbox> hitboxes): _hitboxes(hitboxes) {}
                // Collidable constructor
                collidable(std::vector<utils::hitbox> &hitboxes): _hitboxes(hitboxes) {}
                // Destructor
                ~collidable() {}

                // Check collision with another collidable hitboxes
                bool isColliding(const collidable &other) {
                    for (auto hit : _hitboxes) {
                        for (auto otherHit : other._hitboxes) {
                            if (hit.isColliding(otherHit)) return true;
                        }
                    }
                    return false;
                }

                std::vector<utils::hitbox> _hitboxes;
        };

        class rigidbody {
            public: 
                rigidbody(std::vector<utils::hitbox> hitboxes): _hitboxes(hitboxes) {}

                rigidbody(std::vector<utils::hitbox> &hitboxes): _hitboxes(hitboxes) {}

                ~rigidbody() {}

                bool isColliding(const rigidbody &other) {
                    for (auto hit : _hitboxes) {
                        for (auto otherHit : other._hitboxes) {
                            if (hit.isColliding(otherHit)) return true;
                        }
                    }
                    return false;
                }
                std::vector<utils::hitbox> _hitboxes;
        };
        
    } // namespace comp
} // namespace zef

#endif // ENGINE_MODULES_COLLISION_COMPONENTS_HPP_
