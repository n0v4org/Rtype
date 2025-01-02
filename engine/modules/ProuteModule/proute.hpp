/*
** EPITECH PROJECT, 2025
** RTYPE
** File description:
** proute
*/

#ifndef PROUTE_HPP_
#define PROUTE_HPP_

#include <iostream>
#include "IModule.hpp"

class proute {
    public:

        proute(int p, float o, double d) : puissance(p), odeur(o), degat(d) {
            std::cout << "nouveau pet !" << std::endl;
        }

        int puissance;
        float odeur;
        double degat;
};

class PouteModule: public zef::IModule {
    public:
        PouteModule() {}
        void registerComponents(zef::Engine& engine) {
            engine.registerComponent<proute>();
        }
        void registerSystems(zef::Engine& engine) {
            engine.registerComponent<proute>();
        }
};



#endif /* !PROUTE_HPP_ */

 