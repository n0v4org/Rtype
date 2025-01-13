/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** game
*/

#include "Game.hpp"

namespace rtype {

    Game::Game(zef::Engine &engine)
    : _engine(engine) {
        
    }

    void Game::RegisterGameCmd() {
        register_tcp_game_cmd();
    }

    void Game::launch_game(std::vector<std::string> player_uuid) {
        std::cout << "new game running here" << std::endl;
        while (1) {
            
        }
    }

    void Game::init_game(std::vector<std::string> player_uuid) {
         _games.push_back(std::thread([this, player_uuid](){
            this->launch_game(player_uuid);
         }));
    }

    Game::~Game() {
    }

}
