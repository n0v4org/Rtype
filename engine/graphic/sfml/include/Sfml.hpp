/*
** EPITECH PROJECT, 2024
** zef
** File description:
** SFML DisplayModule
*/

#ifndef ENGINE_GRAPHIC_SFML_INCLUDE_SFML_HPP_
#define ENGINE_GRAPHIC_SFML_INCLUDE_SFML_HPP_

#include <cstddef>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "ADisplayModule.hpp"

namespace zef {
  namespace graph {
    

class Sfml : public ADisplayModule<sf::Texture, sf::SoundBuffer, sf::Font, sf::Shader>{

  public:
    //Sfml *entryPoint();
    ~Sfml();
    Sfml() {

    }

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

    void setCamera(int,int,int) override;
    void moveCamera(int,int,float) override;

    void updateUserInputs(utils::UserInputs& ui) override;

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
  } // namespace graph 
} // namespace zef

#endif // ENGINE_GRAPHIC_SFML_INCLUDE_SFML_HPP_