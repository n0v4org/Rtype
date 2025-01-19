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
  Health(int _hp, int _max) : max(_max), hp(_hp) {
  }
  int hp;
  int max;

  bool up = false;
};

class Owner {
public:
  explicit Owner(size_t _player) : player(_player) {
  }
  size_t player;
};

class Lifetime {
public:
  explicit Lifetime(int _microsecs) : microsecs(_microsecs) {
  }
  int microsecs;
};

class VectorHolder {
public:
  VectorHolder(float _x, float _y) : x(_x), y(_y) {
  }

  float x;
  float y;
};

class Player {
public:
  Player() {
  }
};

class Monster {
public:
  Monster() {
  }
};

class PlayerReplacer {
public:
  PlayerReplacer() {
  }
  size_t time = 0;
};

class Ship {
public:
  Ship() {
  }
};

class Damaged {
public:
  explicit Damaged(int microsec) : _microsec(microsec) {
  }

  int _microsec;
};

class TurretTurnRate {
public:
  TurretTurnRate() {
  }
  int tr = 0;
};

class BackGround {
public:
  BackGround() {
  }
};

class Laser {
public:
  Laser() {
  }
  size_t load = 0.0;
};

class SinusoidalMotion {
public:
  SinusoidalMotion(float amplitude, float frequency, float speedX)
    : amplitude(amplitude), frequency(frequency), speedX(speedX), phase(0.f) {
  }

  float amplitude;
  float frequency;
  float speedX;
  float phase;
};

class MoveCamera {
public:
  MoveCamera() {
  }
};

class SinusoidalAboveMotion {
public:
  SinusoidalAboveMotion(float baseY, float amplitude, float frequency)
    : baseY(baseY), amplitude(amplitude), frequency(frequency), phase(0.f) {
  }

  float baseY;
  float amplitude;
  float frequency;
  float phase;
};


class Plane {
  public:
    Plane() {}
};

class Robot {
  public:
    Robot() {}
};

class Boss {
  public:
    Boss() {}
};


#endif /* !COMPONENTS_HPP_ */
