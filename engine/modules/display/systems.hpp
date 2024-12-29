/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** systems
*/

#ifndef ENGINE_MODULES_DISPLAY_SYSTEMS_HPP_
#define ENGINE_MODULES_DISPLAY_SYSTEMS_HPP_

#include <vector>
#include <algorithm>
#include <string>

#include "../../Engine.hpp"
#include "components.hpp"
#include "../../utils/positions.hpp"

namespace zef
{
    namespace sys
    {
        void draw_drawables(zef::Engine& engine, ecs::sparse_array<comp::drawable>& drawables, ecs::sparse_array<comp::position>& positions) {
            std::vector<int> layers;
            std::cout << "lafjiejaz\n";
            for (auto&& [i, dr, pos]: ecs::indexed_zipper(drawables, positions)) {
            std::cout << "lafjiejaQSDFDqsfQz\n";
                layers.push_back(dr.layer);
            }
            std::sort(layers.begin(), layers.end());
            for (auto l : layers) {
                for (auto&& [i, dr, pos]: ecs::indexed_zipper(drawables, positions)) {
                    if (dr.layer == l) {
                        std::string current_animation = (dr.animation != "" ? dr.animation : dr.loop_animation);
                        if (current_animation == "") continue;
                        engine.GraphLib->drawSprite(current_animation, dr.current_frame, pos.x, pos.y, dr.scaleX, dr.scaleY, 0.0, zef::graph::RGBA({1, 1, 1, 1}));
                    }
                }
            }
        }
        void update_animations(zef::Engine& engine, ecs::sparse_array<comp::drawable>& drawables) {
            
            for (auto&& [i, dr]: ecs::indexed_zipper(drawables)) {
                std::string current_animation = (dr.animation != "" ? dr.animation : dr.loop_animation);
                if (current_animation == "") continue;
                dr.timer += engine.elapsed.count();

                //std::cout << dr.current_frame << std::endl;
                if (dr.timer > static_cast<float>((dr.getAnimationFreq() * 1000) * (1.0 /dr.getAnimationSpeed()))) {
                    if (dr.current_frame >= dr.max_frame_cur() - 1) {
                        dr.current_frame = -1;
                        if (dr.animation != "") dr.animation = "";
                    }
                        dr.current_frame++;
                        dr.timer = 0;
                }
            }
        }  
    } // namespace sys
} // namespace zef


#endif // ENGINE_MODULES_DISPLAY_SYSTEMS_HPP_
