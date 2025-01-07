/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** CommandsClient
*/

#ifndef COMMON_COMMONCOMMANDS_HPP_
#define COMMON_COMMONCOMMANDS_HPP_

#include <cstdlib>

enum Commands {
  CONNECT,
  MOVEPLAYER,
  SHOOTPLAYER,
  SENDPOSITION,

  SPAWNPLAYER,
  SPAWNALLY,
  MOVEALLY,
  SPAWNBULLET,
  SETPLAYERPOS,
  SETALLYPOS,
  ASKPOSITION,
  SPAWNMONSTER,
  KILLMONSTER,
  DEATH,
  DEATHALLY
};

struct CommandDeath {};
struct CommandDeatAlly {
  size_t rep;
};

struct CommandSpawnMonster {
  size_t rep;
  float x;
  float y;
};

struct CommandKillMonster {
  size_t rep;
};

struct CommandSetAllyPos {
  size_t rep;
  float x;
  float y;
};

struct CommandSetPlayerPos {
  float x;
  float y;
};

struct CommandConnect {};

struct CommandMovePlayer {
  float x;
  float y;
};

struct CommandMoveAlly {
  int id;
  float x;
  float y;
};

struct CommandSpawnPlayer {
  size_t replicable;
};

struct CommandSpawnAlly {
  float x;
  float y;
  size_t replicable;
};

struct CommandShoot {};

struct CommandSpawnBullet {
  size_t ship;
};

struct CommandAskPosition {};

struct CommandSendPosition {
  float x;
  float y;
};

#endif  // COMMON_COMMONCOMMANDS_HPP_
