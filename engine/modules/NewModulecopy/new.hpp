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

class comppp1 {
public:
  comppp1(int p, float o, float d) : in(p), fl(o), dou(d) {
    std::cout << "new component comp1 22222222" << std::endl;
  }

  int in;
  float fl;
  float dou;
};

class NewModuleCopy
  : public zef::AModule<zef::Component<comppp1, int, float, float>> {
public:
  NewModuleCopy() : AModule() {
  }
  ~NewModuleCopy() = default;

  void registerSystems(zef::Engine &engine) {
    engine.addSystem<comppp1>(
        "newModuleCopy",
        [](zef::Engine &engine, ecs::sparse_array<comppp1> &comps) {
          for (auto &&[i, c] : ecs::indexed_zipper(comps)) {
            std::cout << "Intttt: " << c.in << ", Floatttttttt: " << c.fl
                      << ", Doubleeeeeeee: " << c.dou << std::endl;
          }
        });
  }

  std::any getMember(const std::string& compname, const std::string& membername) {
    
  }

};

#endif /* !NEW_HPP_ */
