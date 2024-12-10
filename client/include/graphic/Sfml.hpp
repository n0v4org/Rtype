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

class Sfml : public ADisplayModule<sf::Texture, sf::SoundBuffer, sf::Font, sf::Shader>{

  public:
    Sfml *entryPoint();
    ~Sfml();

    void initialize(std::string)override;
    void stop() override;
    void clear() override;
    void refresh() override;
    bool isOpen() override;

    UserInput getEvent() override;

    void storeAssetsPNG(std::string)override;
    void storeAssetsWAV(std::string)override;
    void storeAssetsTTF(std::string)override;
    void storeAssetsVERT(std::string)override;

    //void drawSprite(DrawableSprite_t) override;
    void drawSprite(std::string, std::size_t, int, int, float, float, float, float) override;
    //void drawText(DrawableText_t) override;
    void drawText(std::string, std::string, std::size_t, int, int, float, float, float, float) override;


    void playSound(std::string)override;

    //void saveAnimation(std::string, Animation_t) override;
    void saveAnimation(std::string, std::string, std::size_t, std::size_t, std::size_t, std::size_t) override;

    void moveCamera(int,int,int) override;
  protected:
  private:
    sf::RenderWindow _window;
    std::pair<int,int> _windowSize= std::make_pair(1920,1080);
};

class WindowCreationException : public std::exception {
  public:
    const char* what() const noexcept override {
      return "Failed to open window.";
    }
};
class AssetLoadException : public std::exception {
  public:
    const char* what() const noexcept override {
      return "Failed to load Asset.";
    }
};

}

#endif //CLIENT_INCLUDE_GRAPHIC_SFML_HPP_