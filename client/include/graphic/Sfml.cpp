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

  void Sfml::drawSprite() {};
  void Sfml::drawText() {};


  void storeAssetsPNG(std::string){};
  void storeAssetsWAV(std::string){};
  void storeAssetsTTF(std::string){};
  void storeAssetsVERT(std::string){};

  void playSound(std::string){};

  void saveAnimation(std::pair<std::size_t,std::size_t>,std::pair<std::size_t,std::size_t>,float,std::chrono::milliseconds){};

  void playOnce(std::string,std::string){};
  void playLoop(std::string,std::string){};

  void setAnimationSpeed(std::string,float){};
  void setScale(std::string,std::pair<float,float>){};
  void setPosition(std::string,std::pair<std::size_t,std::size_t>){};
  void setRotation(std::string,float){};

  void moveCamera(std::vector<float>){};

}