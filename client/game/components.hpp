/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** components
*/

#ifndef COMPONENTS_HPP_
#define COMPONENTS_HPP_




class Owner {
    public:
    explicit Owner(size_t _player) : player(_player) {}
    size_t player;
};

class Lifetime {
    public:
    explicit Lifetime(int _microsecs) : microsecs(_microsecs) {} 
    int microsecs;
};

class Player {
    public:
    Player() {}
};

class BackGround {
    public:
    BackGround() {}
};

class Monster {
    public:
    Monster() {}
};

class VectorHolder {
    public:
    VectorHolder(float _x, float _y): x(_x), y(_y) {}

    float x;
    float y;
};




#endif /* !COMPONENTS_HPP_ */

