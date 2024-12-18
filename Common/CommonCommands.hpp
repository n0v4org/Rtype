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
    ASKPOSITION
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
    float velx;
    float vely;
};

#endif // COMMON_COMMONCOMMANDS_HPP_
