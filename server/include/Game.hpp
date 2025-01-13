/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

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
            Game(zef::Engine &_engine);
            void RegisterGameCmd();
            ~Game();

        protected:
        private:
            zef::Engine &_engine;
    };

}

#endif /* !GAME_HPP_ */
