/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** SFML DisplayModule
*/

#ifndef CLIENT_INCLUDE_GRAPHIC_SFML_HPP_
#define CLIENT_INCLUDE_GRAPHIC_SFML_HPP_

#include "./ADisplayModule.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

namespace rtype{

class Sfml : public ADisplayModule<sf::Texture, sf::Sound, sf::Font, sf::Shader>{

  public:
    Sfml *entryPoint();
    ~Sfml();

  protected:
  private:
};

#endif //CLIENT_INCLUDE_GRAPHIC_SFML_HPP_
