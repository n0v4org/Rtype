/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** GameServer
*/

#ifndef GAMESERVER_HPP_
#define GAMESERVER_HPP_

#include <vector>
#include <array>
#include <string>
#include <cmath>
#include <iostream>
#include <map>
#include <random>

#include "Engine.hpp"
#include "Scenes.hpp"
#include "systems.hpp"

#include "CommonCommands.hpp"

#include "modules/display/systems.hpp"
#include "modules/movement/systems.hpp"
#include "modules/network/systems.hpp"

#include "modules/IModule.hpp"

enum {
    SUCCESS = 0,
    NB_ARGS = 1,
};

enum {
    INVALID_ARGS = 0,
    FULL_ROOM = 1,
    LOBBY_NOT_FOUND = 2,
    ALREADY_IN_ROOM = 3,
};

static const char GET_ALL_LOBBY_CMD[] = "GET_ALL_LOBBY";
static const char SET_USERNAME_CMD[] = "SET_USERNAME";
static const char JOIN_ROOM_CMD[] = "JOIN";
static const char SP = ' ';

static const uint16_t NB_TCP_CMD = 3;
static const uint16_t NB_TCP_ERRORS = 4;

static const std::array<std::string, NB_TCP_ERRORS> TCP_ERRORS = {
    "400 invalid args",
    "403 maximum number of players reached",
    "404 room not found",
    "402 player already in lobby",
};

static const std::map<std::string, std::array<std::string, NB_TCP_CMD>> CMD_RES = {
    {GET_ALL_LOBBY_CMD, {"200 ", "0"}},
    {SET_USERNAME_CMD, {"200 Username set successfully to ", "1"}},
    {JOIN_ROOM_CMD, {"200 successfully join room ", "1"}},
};

namespace rtype {

static const uint8_t LOBBY_SIZE = 5;

class GameServer {
    public:
        GameServer(int udp_port, int tcp_port);
        void run();
        ~GameServer();

    protected:
    private:
        void RegisterUdpCmd();
        void RegisterTcpCmd();
        bool tcp_bad_args(input_t input, int nb_args, std::string ec);
        zef::Engine _engine;
        std::map<int, std::string> _usernames;
        std::array<std::vector<int>, LOBBY_SIZE> _lobby;
};

} // namespace rtype
#endif /* !GAMESERVER_HPP_ */
