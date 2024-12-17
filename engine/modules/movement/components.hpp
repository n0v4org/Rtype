/*
** EPITECH PROJECT, 2024
** leVraiRtype
** File description:
** collision
*/

#ifndef ENGINE_MODULES_COLLISION_COMPONENTS_HPP_
#define ENGINE_MODULES_COLLISION_COMPONENTS_HPP_

#include <vector>
#include <string>
#include "../../utils/hitbox.hpp"
#include "../../utils/positions.hpp"

namespace zef {
    namespace comp {
        
        class vector {
            public:
                vector(float posX, float posY, float vec_norm): x(posX), y(posY), norm(vec_norm) {}
                ~vector() = default;

                float x;
                float y;
                float norm;
        };

        class collidable {
            
            public:
                // Collidable constructor
                explicit collidable(std::vector<utils::hitbox> hitboxes): _hitboxes(hitboxes) {}
                // Collidable constructor
                //collidable(std::vector<utils::hitbox> &hitboxes): _hitboxes(hitboxes) {}
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
                std::vector<size_t> _colliding;
        };

        class rigidbody {
            public:

                enum type {
                    STATIC,
                    DYNAMIC
                };

                rigidbody(std::vector<utils::hitbox> hitboxes, type rigidity_type): _hitboxes(hitboxes), _rigidity_type(rigidity_type) {}

                rigidbody(std::vector<utils::hitbox> &hitboxes, type rigidity_type): _hitboxes(hitboxes), _rigidity_type(rigidity_type) {}

                ~rigidbody() {}

                bool isColliding(const rigidbody &other) {
                    for (auto hit : _hitboxes) {
                        for (auto otherHit : other._hitboxes) {
                            if (hit.isColliding(otherHit)) return true;
                        }
                    }
                    return false;
                }

                void setTag(const std::string& tag) {
                    _tags.push_back(tag);
                }

                void setThrough(const std::string& through) {
                    _pass_through.push_back(through);
                }

                type _rigidity_type;
                std::vector<utils::hitbox> _hitboxes;
                std::vector<std::string> _tags;
                std::vector<std::string> _pass_through;
        };
        
    } // namespace comp
} // namespace zef

#endif // ENGINE_MODULES_COLLISION_COMPONENTS_HPP_
