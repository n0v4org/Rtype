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

    void initialize() override;
    void stop() override;
    void clear() override;
    void refresh() override;

    void drawSprite() override;
    void drawText() override;

    Event_t getEvent() override;

  protected:
  private:
    sf::RenderWindow _window;

};

class WindowCreationException : public std::exception {
  public:
    const char* what() const noexcept override {
      return "Failed to open window.";
    }
  };
}

#endif //CLIENT_INCLUDE_GRAPHIC_SFML_HPP_