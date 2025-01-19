/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** UdpProtoCommands
*/

#ifndef UDPPROTOCOMMANDS_HPP_
#define UDPPROTOCOMMANDS_HPP_

enum {
  LOGIN = 0,
  GET_POS = 1,
  SHOOT,

  SEND_POS,
  SHOOT_ALLY,

  SPAWN_PLANE,
  SPAWN_CRAB,
  SPAWN_ROBOT,
  SPAWN_BOSS,

  KILL_MONSTER,

  PLANE_SHOOT,
  CRAB_NEW_DIR,
  ROBOT_NEW_DIR,
  ROBOT_SHOOT,
  BOSS_SHOOT,

  ALLY_UPDATE_HP,
  UPDATE_HP,
  KILL_ALLY,
  KILL,
  TEST
};

enum {
  PWD_ERRORS = 40,
};

// Commands

struct login_t {
  char pwd[21];
};

// Errors

struct pwd_error_t {
  char error[13];
};

struct pos_t {
  float x;
  float y;
};

struct sssend_pos_t {
  float x;
  float y;
  size_t rep;
};

struct shoot_t {
  size_t size;
};

struct shoot_ally_t {
  size_t size;
  size_t rep;
};

struct spawn_plane_t {
  size_t rep;
  float x;
  float y;
};
struct spawn_crab_t {
  size_t rep;
  float x;
  float y;
};
struct spawn_robot_t {
  size_t rep;
  float x;
  float y;
};
struct spawn_boss_t {
  size_t rep;
  float x;
  float y;
};

struct kill_monster_t {
  size_t rep;
};

struct plane_shoot_t {
  size_t rep;
  float vx;
  float vy;
};
struct crab_new_dir_t {
  size_t rep;
  float vx;
  float vy;
  float x;
  float y;
};
struct robot_new_dir_t {
  size_t rep;
  float vx;
  float vy;
  float x;
  float y;
};
struct robot_shoot_t {
  size_t rep;
  float x;
  float y;
};

struct boss_shoot_t {
  size_t rep;
};

struct ally_update_hp_t {
  size_t rep;
  int hp;
};
struct update_hp_t {
  int hp;
};
struct kill_ally_t {
  size_t rep;
};
struct kill_t {};

struct test_t {
  size_t t;
};

#endif /* !UDPPROTOCOMMANDS_HPP_ */
