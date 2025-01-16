/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** IDisplayModule
*/

#ifndef ENGINE_GRAPHIC_INCLUDES_ADISPLAYMODULE_HPP_
#define ENGINE_GRAPHIC_INCLUDES_ADISPLAYMODULE_HPP_

#include <string>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include "IDisplayModule.hpp"
#define M_PI 3.14159265358979323846

namespace zef {
  namespace graph {

    template <typename PNG, typename WAV, typename TTF, typename SHAD,
              typename RECTANGLE>
    class ADisplayModule : public IDisplayModule {
    public:
      ADisplayModule()          = default;
      virtual ~ADisplayModule() = default;
      virtual void initialize(std::string assetFolderPath,
                              std::string windowName,
                              std::pair<int, int> windowSize = {1920,
                                                                1080}) = 0;
      virtual void stop()                                              = 0;
      virtual void clear()                                             = 0;
      virtual void refresh()                                           = 0;
      virtual bool isOpen()                                            = 0;

      void loadAssets(std::string assetFolderPath) override {
        std::string pathname;
        std::string folder_name;
        bool status = false;
        if (std::filesystem::exists(assetFolderPath + "/sprites")) {
          for (const auto &i : std::filesystem::directory_iterator(
                   assetFolderPath + "/sprites")) {
            for (auto &[key, data] : _sprites) {
              if (key == assetFolderPath) {
                status = true;
              }
            }
            if (status) {
              break;
            }
            storeAssetsPNG(i.path().string());
          }
        }
        status = false;
        if (std::filesystem::exists(assetFolderPath + "/fonts")) {
          for (const auto &i : std::filesystem::directory_iterator(
                   assetFolderPath + "/fonts")) {
            for (auto &[key, data] : _fonts) {
              if (key == assetFolderPath) {
                status = true;
              }
            }
            if (status) {
              break;
            }
            storeAssetsTTF(i.path().string());
          }
        }
        status = false;
        if (std::filesystem::exists(assetFolderPath + "/sounds")) {
          for (const auto &i : std::filesystem::directory_iterator(
                   assetFolderPath + "/sounds")) {
            for (auto &[key, data] : _sounds) {
              if (key == assetFolderPath) {
                status = true;
              }
            }
            if (status) {
              break;
            }
            storeAssetsWAV(i.path().string());
          }
        }
        status = false;
        if (std::filesystem::exists(assetFolderPath + "/shaders")) {
          for (const auto &i : std::filesystem::directory_iterator(
                   assetFolderPath + "/shaders")) {
            for (auto &[key, data] : _shaders) {
              if (key == assetFolderPath) {
                status = true;
              }
            }
            if (status) {
              break;
            }
            storeAssetsSHAD(i.path().string());
          }
        }
        if (std::filesystem::exists(assetFolderPath +
                                    "/config/Animations.txt")) {
          configAssetsAnimations(assetFolderPath + "/config/Animations.txt");
        }
        if (std::filesystem::exists(assetFolderPath + "/config/Settings.txt")) {
          configSettings(assetFolderPath + "/config/Settings.txt");
        }
      };

      void configAssetsAnimations(std::string animationConfigPath) override {
        std::ifstream file(animationConfigPath);
        std::string line;

        if (!file.is_open()) {
          return;
        }

        while (std::getline(file, line)) {
          if (line.empty() || line[0] == '#') {
            continue;
          }
          std::istringstream stream(line);
          std::string animationName, spriteSheetName;
          std::size_t startTileX, startTileY, tileSizeX, tileSizeY;

          if (stream >> animationName >> spriteSheetName >> startTileX >>
              startTileY >> tileSizeX >> tileSizeY) {
            saveAnimation(animationName, spriteSheetName, startTileX,
                          startTileY, tileSizeX, tileSizeY);
            std::cout << "Loaded animation :" << animationName << std::endl;
          }
        }
        file.close();
      };
      void configSettings(std::string settingsConfigPath) override {
        std::ifstream file(settingsConfigPath);
        std::string line;

        if (!file.is_open()) {
          return;
        }

        while (std::getline(file, line)) {
          if (line.empty() || line[0] == '#') {
            continue;
          }
          std::istringstream stream(line);
          std::string settingName, settingValue;

          if (stream >> settingName >> settingValue) {
            _settings[settingName] = settingValue;
            std::cout << "Loaded setting :" << settingName << settingValue
                      << std::endl;
          }
        }
        file.close();
      };

      virtual void storeAssetsPNG(std::string assetPath)  = 0;
      virtual void storeAssetsWAV(std::string assetPath)  = 0;
      virtual void storeAssetsTTF(std::string assetPath)  = 0;
      virtual void storeAssetsSHAD(std::string assetPath) = 0;

      virtual void drawSprite(std::string animationName,
                              std::size_t currentFrame, int posX, int posY,
                              float scaleX = 1, float scaleY = 1,
                              float rotation = 0, RGBA mask = {1, 1, 1, 1},
                              std::vector<std::string> objectShaders = {"None"},
                              bool addActive = true)                      = 0;
      virtual void drawText(std::string textString, std::string fontName,
                            std::size_t fontSize, int posX, int posY,
                            float scaleX = 1, float scaleY = 1,
                            float rotation = 0, RGBA mask = {1, 1, 1, 1}) = 0;
      virtual void drawSpriteHUD(
          std::string animationName, std::size_t currentFrame, int posX,
          int posY, float scaleX = 1, float scaleY = 1, float rotation = 0,
          RGBA mask                              = {1, 1, 1, 1},
          std::vector<std::string> objectShaders = {"None"},
          bool addActive                         = true)                         = 0;
      virtual void drawTextHUD(std::string textString, std::string fontName,
                               std::size_t fontSize, int posX, int posY,
                               float scaleX = 1, float scaleY = 1,
                               float rotation = 0,
                               RGBA mask      = {1, 1, 1, 1}) = 0;
      virtual void drawHPBar(float posX, float posY, float width, float height,
                             float value, RGBA backgroundColor,
                             RGBA foregroundColor)       = 0;

      virtual bool playSound(std::string soundName, int volume = 50) = 0;

      virtual void saveAnimation(std::string animationName,
                                 std::string spriteSheetName,
                                 std::size_t startTileX, std::size_t startTileY,
                                 std::size_t tileSizeX,
                                 std::size_t tileSizeY) = 0;

      virtual void setActiveShaders(std::vector<std::string> shaderList = {
                                        "None"}) {
        _activeShaders = shaderList;
      }
      virtual std::vector<std::string> getActiveShaders() {
        return _activeShaders;
      }

      virtual void addParticleEmmiter(
          std::string emmiterName, std::string particleSprite, int posX,
          int posY, int density = 10, int velocity = 4, int lifetime = 1000,
          float scaleX = 1, float scaleY = 1, int rotationStart = 0,
          int rotationRange = 360, RGBA mask = {1, 1, 1, 1},
          std::vector<std::string> objectShaders = {"None"},
          bool addActive                         = true) {
        _particleEmmiters[emmiterName] = {
            particleSprite, posX,          posY,   density,
            velocity,       lifetime,      scaleX, scaleY,
            rotationStart,  rotationRange, mask,   objectShaders,
            addActive};
        for (int i = 0; i < density; i++) {
          _particleEmmiters[emmiterName].particles.push_back(
              {0, 0, velocity - (rand() % velocity / 4),
               static_cast<float>((rand() % rotationRange + rotationStart) *
                                  (M_PI / 180)),
               lifetime, lifetime - (rand() % lifetime / 4)});
        }
      }
      void removeParticleEmmiter(std::string emmiterName) override {
        _particleEmmiters.erase(emmiterName);
      }

      virtual void setCamera(int x, int y, int z)    = 0;
      virtual void moveCamera(int x, int y, float z) = 0;
      virtual std::pair<int,int> getCameraPos() = 0;

      virtual UserInput getEvent()                         = 0;
      virtual void updateUserInputs(utils::UserInputs &ui) = 0;
      void updateSettings(std::string SettingName,
                          std::string SettingValue) override {
        _settings[SettingName] = SettingValue;
      }
      std::string getSetting(std::string SettingName){
        return _settings[SettingName];
      }

    protected:
      std::vector<std::string> _activeShaders;
      std::map<std::string, PNG> _sprites;
      std::map<std::string, WAV> _sounds;
      std::map<std::string, TTF> _fonts;
      std::map<std::string, SHAD> _shaders;

      std::map<std::string, Animation_t> _animations;
      std::map<std::string, std::string> _settings;
      std::map<std::string, ParticleEmmiter_t> _particleEmmiters;

      RECTANGLE _rectangle;

    private:
    };
  }  // namespace graph
}  // namespace zef

#endif  // ENGINE_GRAPHIC_INCLUDES_ADISPLAYMODULE_HPP_