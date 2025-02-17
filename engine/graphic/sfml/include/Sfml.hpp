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
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "HPBar.hpp"
#include "ADisplayModule.hpp"

namespace zef {
  namespace graph {

    class Sfml
      : public ADisplayModule<std::pair<sf::Sprite, sf::Texture>,
                              std::pair<sf::Sound, sf::SoundBuffer>,
                              sf::Font,
                              sf::Shader, sf::RectangleShape> {
    public:
      ~Sfml();
      Sfml() {
      }

      void initialize(std::string assetFolderPath, std::string windowName,
                      std::pair<int, int> windowSize = {1920, 1080}) override;
      void stop() override;
      void clear() override;
      void refresh() override;
      bool isOpen() override;

      void storeAssetsPNG(std::string assetPath) override;
      void storeAssetsWAV(std::string assetPath) override;
      void storeAssetsTTF(std::string assetPath) override;
      void storeAssetsSHAD(std::string assetPath) override;

      void drawSprite(std::string animationName, std::size_t currentFrame,
                      int posX, int posY, float scaleX = 1, float scaleY = 1,
                      float rotation = 0, RGBA mask = {1, 1, 1, 1},
                      std::vector<std::string> objectShaders = {"None"},
                      bool addActive                         = true) override;
      void drawText(std::string textString, std::string fontName,
                    std::size_t fontSize, int posX, int posY, float scaleX = 1,
                    float scaleY = 1, float rotation = 0,
                    RGBA mask = {1, 1, 1, 1}) override;
      void drawSpriteHUD(std::string animationName, std::size_t currentFrame,
                         int posX, int posY, float scaleX = 1, float scaleY = 1,
                         float rotation = 0, RGBA mask = {1, 1, 1, 1},
                         std::vector<std::string> objectShaders = {"None"},
                         bool addActive = true) override;
      void drawTextHUD(std::string textString, std::string fontName,
                       std::size_t fontSize, int posX, int posY,
                       float scaleX = 1, float scaleY = 1, float rotation = 0,
                       RGBA mask = {1, 1, 1, 1}) override;
      void drawHPBar(float posX, float posY, float width, float height,
                     float value, RGBA backgroundColor,
                     RGBA foregroundColor) override;

      void drawRectangle(float posX, float posY, float wigth, float height, RGBA color) override;

      bool playSound(std::string soundName, int volume = 50) override;

      void saveAnimation(std::string, std::string, std::size_t, std::size_t,
                         std::size_t, std::size_t) override;

      void setCamera(int, int, int) override;
      void moveCamera(int, int, float) override;
      std::pair<int,int> getCameraPos() override;

      UserInput getEvent() override;
      void updateUserInputs(utils::UserInputs& ui) override;

    protected:
    private:
      RGBA colorBlindMask;

      void drawShaders(sf::Sprite sprite,
                       std::vector<std::string>& objectShaders, bool addActive);
      void applyShaders(sf::Sprite& sprite,
                        std::vector<std::string>& shaderNames);
      sf::Color colorBlindness(RGBA mask);
      void drawParticleEmmiters();
      std::vector<std::string> splitstring(const std::string& str,
                                           const char& ch);

      sf::RenderWindow _window;
      HPBar _hpBar;
      std::pair<int, int> _windowSize = std::make_pair(1920, 1080);
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
  }  // namespace graph
}  // namespace zef

#endif  // ENGINE_GRAPHIC_SFML_INCLUDE_SFML_HPP_