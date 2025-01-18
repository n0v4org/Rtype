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

#endif /* !COMPONENTS_HPP_ */
