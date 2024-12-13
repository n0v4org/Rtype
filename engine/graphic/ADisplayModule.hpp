/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** IDisplayModule
*/

#ifndef CLIENT_INCLUDE_GRAPHIC_ADISPLAYMODULE_HPP_
#define CLIENT_INCLUDE_GRAPHIC_ADISPLAYMODULE_HPP_

#include "./IDisplayModule.hpp"

namespace zef{
namespace graph{

template<typename PNG, typename WAV, typename TTF, typename VERT>
class ADisplayModule : public IDisplayModule{
  public:
    ADisplayModule()=default;
    virtual ~ADisplayModule()=default;
    virtual void initialize(std::string assetFolderPath, std::string windowName) = 0;
    virtual void stop() = 0;
    virtual void clear() = 0;
    virtual void refresh() = 0;
    virtual bool isOpen() = 0;


    void loadAssets(std::string assetFolderPath) override{
      std::string pathname;
      std::string folder_name;
      bool status = false;
      if (std::filesystem::exists(assetFolderPath + "/sprites")) {
        for (const auto &i: std::filesystem::directory_iterator(assetFolderPath + "/sprites")) {
          for (auto &[key, data]: _sprites) {
            if (key == assetFolderPath) {
              status = true;
            }
          }
          if (status) {
            break;
          }
          storeAssetsPNG(i.path());
        }
      }
      status = false;
      if (std::filesystem::exists(assetFolderPath + "/fonts")) {
        for (const auto &i: std::filesystem::directory_iterator(assetFolderPath + "/fonts")) {
          for (auto &[key, data]: _fonts) {
            if (key == assetFolderPath) {
              status = true;
            }
          }
          if (status) {
            break;
          }
          storeAssetsTTF(i.path());
        }
      }
      status = false;
      if (std::filesystem::exists(assetFolderPath + "/sounds")) {
        for (const auto &i: std::filesystem::directory_iterator(assetFolderPath + "/sounds")) {
          for (auto &[key, data]: _sounds) {
            if (key == assetFolderPath) {
              status = true;
            }
          }
          if (status) {
            break;
          }
          storeAssetsWAV(i.path());
        }
      }
      status = false;
      if (std::filesystem::exists(assetFolderPath + "/shaders")) {
        for (const auto &i: std::filesystem::directory_iterator(assetFolderPath + "/shaders")) {
          for (auto &[key, data]: _shaders) {
            if (key == assetFolderPath) {
              status = true;
            }
          }
          if (status) {
            break;
          }
          storeAssetsVERT(i.path());
        }
      }
      if (std::filesystem::exists(assetFolderPath + "/config/Animations.txt")) {
        configAssetsAnimations(assetFolderPath + "/config/Animations.txt");
      }

    };

    void configAssetsAnimations(std::string assetPath) override{
      std::ifstream file(assetPath);
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

        if (stream >> animationName >> spriteSheetName >> startTileX >> startTileY >> tileSizeX >> tileSizeY) {
          saveAnimation(animationName, spriteSheetName, startTileX, startTileY, tileSizeX, tileSizeY);
          std::cout << "Loaded animation :" << animationName << std::endl;
        }
      }
      file.close();
    };

    virtual void storeAssetsPNG(std::string assetPath)=0;
    virtual void storeAssetsWAV(std::string assetPath)=0;
    virtual void storeAssetsTTF(std::string assetPath)=0;
    virtual void storeAssetsVERT(std::string assetPath)=0;

    virtual void drawSprite(std::string animationName, std::size_t currentFrame, int posX, int posY, float scaleX, float scaleY, float rotation, float opactiy) = 0;
    virtual void drawText(std::string textString, std::string fontName, std::size_t fontSize, int posX, int posY, float scaleX, float sclaeY, float rotation, float opacity) = 0;
    virtual void drawSpriteHUD(std::string animationName, std::size_t currentFrame, int posX, int posY, float scaleX, float scaleY, float rotation, float opactiy) = 0;
    virtual void drawTextHUD(std::string textString, std::string fontName, std::size_t fontSize, int posX, int posY, float scaleX, float sclaeY, float rotation, float opacity) = 0;

    virtual void playSound(std::string soundName) = 0;

    virtual void saveAnimation(std::string animationName, std::string spriteSheetName, std::size_t startTileX, std::size_t startTileY, std::size_t tileSizeX, std::size_t tileSizeY) = 0;

    virtual void setCamera(int x, int y, int z)=0;
    virtual void moveCamera(int x, int y, float z)=0;

    virtual UserInput getEvent() = 0;
    virtual void updateUserInputs(utils::UserInputs& ui) = 0;

  protected:
    std::map<std::string,Animation_t> _animations;

    std::map<std::string,PNG> _sprites;
    std::map<std::string,WAV> _sounds;
    std::map<std::string,TTF> _fonts;
    std::map<std::string,VERT> _shaders;
  private:

};

}
}

#endif //CLIENT_INCLUDE_GRAPHIC_ADISPLAYMODULE_HPP_