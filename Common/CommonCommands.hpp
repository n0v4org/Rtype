/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** CommandsClient
*/

#ifndef COMMON_COMMONCOMMANDS_HPP_
#define COMMON_COMMONCOMMANDS_HPP_

enum Commands {
    CONNECT,
    MOVEPLAYER,


    SPAWNPLAYER,
    SPAWNALLY,
    MOVEALLY
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

#endif // COMMON_COMMONCOMMANDS_HPP_

