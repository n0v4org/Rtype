/*
** EPITECH PROJECT, 2025
** RTYPE
** File description:
** proute
*/

#ifndef PROUTE_HPP_
#define PROUTE_HPP_

#include <iostream>
#include "AModule.hpp"
#include "Engine.hpp"

  class proute {
  public:
    proute(int p, float o, double d) : puissance(p), odeur(o), degat(d) {
      std::cout << "nouveau pet !" << std::endl;
    }

    int puissance;
    float odeur;
    double degat;
  };


  class ProuteModule : public zef::AModule<
      zef::Component<proute, int, float, double>
    > {
      public:
        ProuteModule() : AModule() {}
        ~ProuteModule() = default;

        void registerSystems(zef::Engine &engine) {
          engine.addSystem<proute>([](zef::Engine &engine, ecs::sparse_array<proute> &proutes){
            for (auto &&[i, p] : ecs::indexed_zipper(proutes)) {
              std::cout << "Puissance: " << p.puissance << ", Odeur: " << p.odeur << ", Damage: " << p.degat << std::endl;
            }
          });
        }
  };


#endif /* !PROUTE_HPP_ */
