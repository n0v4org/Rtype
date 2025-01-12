/*
** EPITECH PROJECT, 2025
** RTYPE
** File description:
** scenes
*/

#include "Engine.hpp"

#include "Patrons.hpp"



class MenuScene {
    public:
        static void loadScene(zef::Engine& engine) {
            engine.instanciatePatron<BackGroundPatron>();
            engine.instanciatePatron<ButtonPatron>(0.0f, 0.0f);
        }
};

class GameScene {
    public:
        static void loadScene(zef::Engine& engine) {
            engine.instanciatePatron<BackGroundGamePatron>();
            engine.instanciatePatron<CardPatron>(5, 2);
        }
};