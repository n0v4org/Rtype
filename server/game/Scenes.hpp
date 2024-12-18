/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** Scenes
*/

#ifndef SCENES_HPP_
#define SCENES_HPP_

#include "Engine.hpp"

#include "PlayerPatron.hpp"
#include "BulletPatron.hpp"
#include "EnemyPatron.hpp"
#include "events.hpp"

class LevelScene {
public:
    static void loadScene(zef::Engine& engine) {
        //engine.instanciatePatron<PlayerPatron>(0.0f, 150.0f);
        //ecs::Entity e = engine.instanciatePatron<PlayerPatron>(0.0f, -150.0f);
        //engine.instanciatePatron<EnemyPatron>(600.0f, -150.0f);
        
        //engine.sendEvent<SetPlayerVectorEvent>(e, 1.0f, 0.0f);

        //engine.instanciatePatron<BulletPatron>(0.0f, 0.0f);
    }

    
};

class LobbyScene {
public:
    static void loadScene(zef::Engine& engine) {
        
    }

    
};


#endif /* !SCENES_HPP_ */

