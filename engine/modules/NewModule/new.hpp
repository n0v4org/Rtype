/*
** EPITECH PROJECT, 2025
** RTYPE
** File description:
**
*/

#ifndef NEW_HPP_
#define NEW_HPP_

#include <iostream>
#include <map>

#include "AModule.hpp"
#include "Engine.hpp"

class comp1 {
public:
  comp1(int p, float o, float d) : in(p), fl(o), dou(d) {
    std::cout << "new component comp1" << std::endl;
  }

  int in;
  float fl;
  float dou;
};

class comp2 {
public:
  explicit comp2(int d) : degat(d) {
    std::cout << "new component comp2" << std::endl;
  }

  int degat;
};

class NewModule : public zef::AModule<zef::Component<comp1, int, float, float>,

                                      zef::Component<comp2, int> > {
public:
  NewModule() : AModule() {
  }
  ~NewModule() = default;

  void registerSystems(zef::Engine &engine) {
    engine.addSystem<comp1>(
        "newModule", [](zef::Engine &engine, ecs::sparse_array<comp1> &comps) {
          for (auto &&[i, c] : ecs::indexed_zipper(comps)) {
            std::cout << "Int: " << c.in << ", Float: " << c.fl
                      << ", Double: " << c.dou << std::endl;
          }
        });

    engine.addSystem<comp1>(
        "newModule", [](zef::Engine &engine, ecs::sparse_array<comp1> &comps) {
          for (auto &&[i, c] : ecs::indexed_zipper(comps)) {
            std::cout << "AAInt: " << c.in << ", AAFloat: " << c.fl
                      << ", AADouble: " << c.dou << std::endl;
          }
        });
  }
};

#endif /* !NEW_HPP_ */
