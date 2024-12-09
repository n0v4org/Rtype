/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** SFML DisplayModule
*/

#include "./Sfml.hpp"

namespace rtype{

  extern "C" Sfml *entryPoint() {
    return new Sfml;
  }

  void Sfml::initialize()
  {
    _window.create(sf::VideoMode(1920, 1080), "Arcade");

    if (!_window.isOpen()) {
      throw WindowCreationException();
      return;
    }
    _window.setFramerateLimit(60);

    sf::String path = "Assets/";
    loadAssets(path);
  }

  void Sfml::refresh() {
    _window.display();
  }

  void Sfml::clear() {
    _window.clear();
  }

  void Sfml::stop() {
    _window.close();
  }

  Sfml::~Sfml() {
  }


  void Sfml::drawSprite() {}
  void Sfml::drawText() {}

}