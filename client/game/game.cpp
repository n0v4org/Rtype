/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** game
*/

#include <string>
#include "Engine.hpp"
#include "Scenes.hpp"        // pour MenuScene, ...
#include "systems.hpp"

// Modules de rendu / mouvement, 
// on peut en commenter certains pour ne pas se surcharger
#include "modules/display/systems.hpp"
#include "modules/movement/systems.hpp"
#include "modules/network/systems.hpp"
#include "modules/controller/systems.hpp"

// #include "asio.hpp"     // si pas nécessaire, on peut enlever
// #include "CommonCommands.hpp" // si pas nécessaire, on peut enlever

void runClient(int /*sport*/, int /*cport*/, std::string /*ip*/) {
    zef::Engine engine;

    // 1) Initialisation de la librairie graphique (dossier "Assets", titre de la fenêtre vide)
    engine.initGraphLib("Assets", "");

    // 2) On enregistre l'image "menu.jpg" comme une animation "menu"
    //    Suppose que "menu.jpg" se trouve dans "Assets/menu.jpg"
    //    On précise 1920x1080 comme taille du sprite, ajustez si différent
    engine.GraphLib->saveAnimation("menu", "menu", 0, 0, 1920, 1080);

    // 3) Enregistrement des composants nécessaires
    //    - position, drawable : indispensables pour afficher
    //    - BackGround (votre composant, même si vide)
    engine.registerComponent<zef::comp::position>();
    engine.registerComponent<zef::comp::drawable>();
    engine.registerComponent<BackGround>(); 

    // (Si besoin, enregistrez d'autres composants, 
    //  mais pour un background statique, c'est déjà suffisant)

    // 4) On déclare seulement les systèmes utiles au dessin (dessiner l'image)
    //    a) Mécanique : mise à jour des entrées (optionnel)
    engine.addSystem<>("zefir", zef::sys::update_user_inputs);

    //    b) Système d'animations (optionnel, mais si vous utilisez playAnimationLoop)
    engine.addSystem<zef::comp::drawable>("zefir", zef::sys::update_animations);

    //    c) Système d’affichage
    engine.addSystem<zef::comp::drawable, zef::comp::position>(
        "zefir", zef::sys::draw_drawables
    );

    // (Systèmes supplémentaires si besoin, 
    //  mais on veut un minimum pour ne pas bouger le background)

    // 5) Enregistrement de notre nouvelle scène "MenuScene"
    engine.registerScene<MenuScene>("menu");

    // 6) Charger la scène "menu" => affichera juste l'image de fond
    engine.loadScene("menu");

    // 7) Lancement de la boucle principale
    engine.run(); 
}
