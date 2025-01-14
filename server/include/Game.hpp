/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <thread>
#include <string>

#include "Engine.hpp"
#include "Scenes.hpp"
#include "systems.hpp"

#include "CommonCommands.hpp"

#include "modules/display/systems.hpp"
#include "modules/movement/systems.hpp"
#include "modules/network/systems.hpp"

#include "modules/IModule.hpp"


namespace rtype {

    class Game {
        public:
            Game();
            void RegisterGameCmd();
            void launch_game(std::vector<std::string> player_uuid, int tcp_port, int udp_port);
            void init_game(std::vector<std::string> player_uuid, int tcp_port, int udp_port);
            ~Game();

        protected:
        private:
            std::vector<std::thread> _games;
            void register_tcp_game_cmd();
            zef::Engine _engine;
    };

}

#endif /* !GAME_HPP_ */
