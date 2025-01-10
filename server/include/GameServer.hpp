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
#include <cmath>
#include <iostream>
#include <random>

#include "Engine.hpp"
#include "Scenes.hpp"
#include "systems.hpp"

#include "CommonCommands.hpp"

#include "modules/display/systems.hpp"
#include "modules/movement/systems.hpp"
#include "modules/network/systems.hpp"

#include "modules/IModule.hpp"

namespace rtype {

static const uint8_t LOBBY_SIZE = 5;

class GameServer {
    public:
        GameServer(int udp_port, int tcp_port);
        void RegisterTcpCmd();
        void RegisterUdpCmd();
        void run();
        ~GameServer();

    protected:
    private:
        zef::Engine _engine;
        std::vector<std::array<int, LOBBY_SIZE>> _lobby;
};

} // namespace rtype
#endif /* !GAMESERVER_HPP_ */
