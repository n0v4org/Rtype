/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** events
*/

#ifndef GEVENTS_HPP_
#define GEVENTS_HPP_

struct GetHittedByBullet {
  size_t bullet;
  int damage;
};
struct DestroyBullet {};

struct SetPlayerVectorEvent {
  float x;
  float y;
};
struct ShootPlayerEvent {};
struct LoadShoot {};

struct OnDeath {};


struct TurretTurn {
  int angle; // 0 up 1 diag 2 side
};

struct SetEnemyVectorEvent {
    float vx;
    float vy;
};

struct PlaneShootEvent {
    float vx;
    float vy;
};

struct SetEnemyPos {
  float px;
  float py;
};


#endif /* !EVENTS_HPP_ */
