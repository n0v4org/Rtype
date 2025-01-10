/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** game
*/

#include <vector>
#include <cmath>
#include <iostream>
#include <random>

#include "GameServer.hpp"

static const char GET_ALL_LOBBY[] = "GET_ALL_LOBBY";

namespace rtype {

    GameServer::GameServer(int udp_port, int tcp_port) {
        _engine.initServer(udp_port, tcp_port);
        RegisterTcpCmd();
        RegisterUdpCmd();
        _engine.addSystem<>("zefir", zef::sys::handle_server);
    }

    void GameServer::run() {
        std::cout << "Running" << std::endl;
        _engine.run();
    }

    void GameServer::RegisterTcpCmd() {
        _engine.registerCommandTcp(GET_ALL_LOBBY, [this ](zef::Engine& engine, std::string payload) {
            std::string _res;
            
            for (int i = 0; i < _lobby.size(); i++) {
                
            }
        });
    }

    void GameServer::RegisterUdpCmd() {

    }

    GameServer::~GameServer() {

    }

} // namespace rtype