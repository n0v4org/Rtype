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
  explicit Owner(size_t _player) : player(_player) {
  }
  size_t player;
};

class Health {
public:
  Health(size_t hp, size_t max) : _hp(hp), _max(max) {
  }

  size_t _hp;
  size_t _max;
};

class Lifetime {
public:
  explicit Lifetime(int _microsecs) : microsecs(_microsecs) {
  }
  int microsecs;
};

class Player {
public:
  Player() {
  }
};
class Ship {
public:
  Ship() {
  }
};

class BackGround {
public:
  BackGround() {
  }
};

class Monster {
public:
  Monster() {
  }
};

class Laser {
public:
  Laser() {
  }
  size_t load = 0.0;
};

class VectorHolder {
public:
  VectorHolder(float _x, float _y) : x(_x), y(_y) {
  }

  float x;
  float y;
};

class SounbdBar {
public:
  SounbdBar() {}
};

#endif /* !COMPONENTS_HPP_ */
