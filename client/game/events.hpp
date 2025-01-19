/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** events
*/

#ifndef GEVENTS_HPP_
#define GEVENTS_HPP_

struct GetHittedByBullet {};

struct GetHittedByMonster {};

struct GetHittedByMonsterBullet {};

struct GetHittedByPlayer {};

struct DestroyBullet {};

struct SetPlayerVectorEvent {
  float x;
  float y;
};
struct ShootPlayerEvent {
  size_t size;
};
struct LoadShoot {};

struct OnDeath {};

struct TurretTurn {
  int angle;  // 0 up 1 diag 2 side
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

struct RobotShoot {};

struct MiniBossShoot {
  float vx;
  float vy;
};

struct BossShoot {};

#endif /* !EVENTS_HPP_ */
