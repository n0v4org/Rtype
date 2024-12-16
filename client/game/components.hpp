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
    Owner(size_t _player) : player(_player) {}
    size_t player;
};

class Lifetime {
    public:
    Lifetime(int _microsecs) : microsecs(_microsecs) {} 
    int microsecs;
};

class Player {
    public:
    Player() {}
};


#endif /* !COMPONENTS_HPP_ */

