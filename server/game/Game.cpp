/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** game
*/

#include "Game.hpp"

namespace rtype {

    Game::Game()
    {
    }

    void Game::RegisterGameCmd() {
        register_tcp_game_cmd();
    }

    void Game::launch_game(std::vector<std::string> player_uuid, int tcp_port, int udp_port) {
        std::cout << "new game running here" << std::endl;
        std::cout << tcp_port << udp_port << std::endl;
        _engine.initServer(udp_port, tcp_port);
    }

    void Game::init_game(std::vector<std::string> player_uuid, int tcp_port, int udp_port) {
         _games.push_back(std::thread([this, player_uuid, tcp_port, udp_port](){
            this->launch_game(player_uuid, tcp_port, udp_port);
         }));
    }

    Game::~Game() {
    }

}
