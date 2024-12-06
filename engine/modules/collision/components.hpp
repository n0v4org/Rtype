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
        class collidable {
            public:
            
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
        
    } // namespace comp
} // namespace zef

#endif // ENGINE_MODULES_COLLISION_COMPONENTS_HPP_
