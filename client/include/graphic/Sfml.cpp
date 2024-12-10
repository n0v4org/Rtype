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

  void Sfml::initialize(std::string path) {

    _window.create(sf::VideoMode(_windowSize.first, _windowSize.second), "RType");

    if (!_window.isOpen()) {
      throw WindowCreationException();
      return;
    }
    _window.setFramerateLimit(60);

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

  

  UserInput Sfml::getEvent(){
    UserInput userInput;

    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          userInput.Close = true;
		if (event.type == sf::Event::KeyPressed) {
      		if (event.text.unicode == 3 ) { userInput.Pressed_D = true;}
      		if (event.text.unicode == 8 ) { userInput.Pressed_I = true;}
      		if (event.text.unicode == 9 ) { userInput.Pressed_J = true;}
      		if (event.text.unicode == 10) { userInput.Pressed_K = true;}
      		if (event.text.unicode == 11) { userInput.Pressed_L = true;}
      		if (event.text.unicode == 12) { userInput.Pressed_M = true;}
      		if (event.text.unicode == 15) { userInput.Pressed_P = true;}
      		if (event.text.unicode == 16) { userInput.Pressed_Q = true;}
      		if (event.text.unicode == 18) { userInput.Pressed_S = true;}
      		if (event.text.unicode == 25) { userInput.Pressed_Z = true;}
		}
    }
    return userInput;
  };

}