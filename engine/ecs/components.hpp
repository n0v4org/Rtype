/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** components
*/

#ifndef COMPONENTS_HPP_
#define COMPONENTS_HPP_

#include <string>

enum INPUT {
    NONE,
    Z,
    Q,
    S,
    D
};

enum SHAPE {
    CIRCLE,
    SQUARE
};

namespace component {
    struct position {
        float x;
        float y;
    };

    struct collidable {
        std::string type;
    };
    

    struct velocity {
        float vx;
        float vy;
    };

    struct drawable {
        short r;
        short g;
        short b;
        SHAPE shape;
    };

    struct controllable {
        INPUT input;
    };
};



#endif /* !COMPONENTS_HPP_ */
