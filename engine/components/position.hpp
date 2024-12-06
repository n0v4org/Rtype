/*
** EPITECH PROJECT, 2024
** leVraiRtype
** File description:
** position
*/

#ifndef ENGINE_COMPONENTS_POSITION_HPP_
#define ENGINE_COMPONENTS_POSITION_HPP_

namespace zef {
    namespace comp {
        class position {
            public:
                position(float posX, float posY): x(posX), y(posY) {}
                ~position() = default;

                float x;
                float y;
        };
    } // namespace comp
} // namespace zef

#endif // ENGINE_COMPONENTS_POSITION_HPP_
