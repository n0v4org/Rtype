/*
** EPITECH PROJECT, 2024
** zef
** File description:
** SFML DisplayModule
*/

#ifndef CLIENT_INCLUDE_GRAPHIC_SFML_HPP_
#define CLIENT_INCLUDE_GRAPHIC_SFML_HPP_

#include "../ADisplayModule.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

namespace zef{
namespace graph{

class Sfml : public ADisplayModule<std::pair<sf::Sprite,sf::Texture>, sf::SoundBuffer, sf::Font, sf::Shader>{

  public:
    ~Sfml();
    Sfml() {}

    void initialize(std::string assetFolderPath, std::string windowName)override;
    void stop() override;
    void clear() override;
    void refresh() override;
    bool isOpen() override;


    void storeAssetsPNG(std::string assetPath)override;
    void storeAssetsWAV(std::string assetPath)override;
    void storeAssetsTTF(std::string assetPath)override;
    void storeAssetsVERT(std::string assetPath)override;

    void drawSprite(std::string animationName, std::size_t currentFrame, int posX, int posY, float scaleX, float scaleY, float roation, RGBA mask) override;
    void drawText(std::string textString, std::string fontName, std::size_t fontSize, int posX, int posY, float scaleX, float scaleY, float roation, RGBA mask) override;
    void drawSpriteHUD(std::string animationName, std::size_t currentFrame, int posX, int posY, float scaleX, float scaleY, float roation, RGBA mask) override;
    void drawTextHUD(std::string textString, std::string fontName, std::size_t fontSize, int posX, int posY, float scaleX, float scaleY, float roation, RGBA mask) override;

    void playSound(std::string)override;

    void saveAnimation(std::string, std::string, std::size_t, std::size_t, std::size_t, std::size_t) override;

    void setCamera(int,int,int) override;
    void moveCamera(int,int,float) override;

    UserInput getEvent() override;
    void updateUserInputs(utils::UserInputs& ui) override;

  protected:
  private:
    sf::RenderWindow _window;
    std::pair<int,int> _windowSize= std::make_pair(1920,1080);
    std::map<std::string, sf::View> _views;

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
}

#endif //CLIENT_INCLUDE_GRAPHIC_SFML_HPP_