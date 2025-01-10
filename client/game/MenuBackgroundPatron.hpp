#ifndef MENU_BACKGROUND_PATRON_HPP_
#define MENU_BACKGROUND_PATRON_HPP_

#include "Engine.hpp"
#include "components.hpp"              // pour BackGround
#include "modules/movement/components.hpp" // pour zef::comp::position
#include "modules/display/components.hpp"   // pour zef::comp::drawable

class MenuBackgroundPatron {
public:
    static void instanciate(zef::Engine &engine, const ecs::Entity &self) {
        // On place le background à la position (0, 0).
        engine.addEntityComponent<zef::comp::position>(self, 0.f, 0.f);

        // Composant perso "BackGround" (vide si vous voulez juste marquer que c'est un BG).
        engine.addEntityComponent<BackGround>(self);

        // Composant drawable avec une seule animation nommée "menu"
        // (on suppose que vous l’avez déjà chargée via "engine.GraphLib->saveAnimation(...)")
        zef::comp::drawable dr;
        // Ajout d'une animation "menu" (1 frame, durée 200 ms, arbitraire si non animé)
        dr.addAnimation("menu", 1, 200);
        // On la joue en boucle (même si 1 frame, ça ne fera pas de différence)
        dr.playAnimationLoop("menu", 1);
        // Mettre le layer en négatif pour qu'il soit derrière d'autres sprites, si nécessaire
        dr.layer = -6;
        // Ajuster l'échelle si besoin. Si votre image fait déjà 1920x1080, vous pouvez laisser (1,1).
        dr.setScale(1.0f, 1.0f);

        // On attache ce composant "drawable" à l'entité
        engine.addEntityComponent<zef::comp::drawable>(self, dr);
    }
};

#endif // MENU_BACKGROUND_PATRON_HPP_
