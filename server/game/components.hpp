/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** components
*/

#ifndef COMPONENTS_HPP_
#define COMPONENTS_HPP_

#include <algorithm>


class Health {
    public:
    Health(int _hp, int _max) : max(_max), hp(_hp) {}
    int hp;
    int max;
};

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


class VectorHolder {
    public:
    VectorHolder(float _x, float _y): x(_x), y(_y) {}

    float x;
    float y;
};

class Player {
    public:
    Player(){}

};

class Monster {
    public:
    Monster(){}

};

class PlayerReplacer {
    public:
    PlayerReplacer(){}
    size_t time = 0;
};


#endif /* !COMPONENTS_HPP_ */

