/*
** EPITECH PROJECT, 2025
** RTYPE
** FILE description:
** Module test
*/

#ifndef TEST_HPP_
#define TEST_HPP_

#include <iostream>

#include "AModule.hpp"
#include "Engine.hpp"

class ExampleComp1 {
public:
  ExampleComp1(int a, float b) : _a(a), _b(b) {
  }

  int _a;
  float _b;
};

class ExampleComp2 {
public:
  ExampleComp2(float a, char b) : _a(a), _b(b) {
  }

  float _a;
  char _b;
};

void exampleSystem(zef::Engine &engine, ecs::sparse_array<ExampleComp1> &comps1,
                   ecs::sparse_array<ExampleComp2> &comps2) {
  for (auto [i, c1, c2] : ecs::indexed_zipper(comps1, comps2)) {
    engine.consoleSendMessage("OAUI OUAI OUAI");
  }
}

class test
  : public zef::AModule<
        zef::Component<ExampleComp1, int,
                       float>,  // Name of component 1 and there attributes
                                // types in the same order than the constructor
        zef::Component<ExampleComp2, float,
                       char>  // Name of component 2 and there attributes types
                              // in the same order than the constructor
        > {
public:
  test() : AModule() {
  }
  ~test() = default;

  void registerSystems(zef::Engine &engine) {
    engine.addSystem<ExampleComp1, ExampleComp2>("test", exampleSystem);
  }
};

#endif /* !TEST_HPP_ */
