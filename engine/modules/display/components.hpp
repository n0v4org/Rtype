/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** components
*/

#ifndef COMPONENTS_HPP_
#define COMPONENTS_HPP_

#include "../../Engine.hpp"

namespace zef
{
    namespace comp
    {
        class drawable {
            public:
                drawable() {

                }

                void addAnimation(const std::string& name, size_t size, size_t freq) {
                    _animation_sizes[name] = {size, freq};
                }

                void playAnimation(const std::string& name, float sspeed) {
                    current_frame = 0;
                    animation = name;
                    speed = sspeed;
                }

                void playAnimationLoop(const std::string& name, float speed) {
                    current_frame = 0;
                    loop_animation = name;
                    loop_animation_speed = speed;
                }

                size_t max_frame_cur() {
                    if (animation != "") return _animation_sizes[animation].first;
                    return _animation_sizes[loop_animation].first;
                }

                size_t getAnimationFreq() {
                    
                    if (animation != "") {
                        return _animation_sizes[animation].second;
                    }
                    return _animation_sizes[loop_animation].second;
                }

                float getAnimationSpeed() {
                    if (animation != "") {
                        return speed;
                    } 
                    return loop_animation_speed;
                }

                size_t current_frame = 0;

                std::string loop_animation = "";
                float loop_animation_speed;

                std::string animation = "";
                float speed;


                size_t timer = 0;

                std::map<std::string, std::pair<size_t, size_t>> _animation_sizes;

                
        };
    } // namespace comp
    
} // namespace zef


#endif /* !COMPONENTS_HPP_ */
