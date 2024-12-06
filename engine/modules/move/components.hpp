/*
** EPITECH PROJECT, 2024
** leVraiRtype
** File description:
** position
*/

#ifndef ENGINE_MODULES_MOVE_COMPONENTS_HPP_
#define ENGINE_MODULES_MOVE_COMPONENTS_HPP_

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
    } // namespace comp
} // namespace zef

#endif // ENGINE_MODULES_MOVE_COMPONENTS_HPP_
