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



#endif /* !PROUTE_HPP_ */
