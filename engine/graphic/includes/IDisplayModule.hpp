/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** IDisplayModule
*/

#ifndef ENGINE_GRAPHIC_INCLUDES_IDISPLAYMODULE_HPP_
#define ENGINE_GRAPHIC_INCLUDES_IDISPLAYMODULE_HPP_

#include <cstdio>
#include <utility>
#include <chrono>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../../utils/inputsUtils.hpp"
#include "../sfml/include/HPBar.hpp"

namespace zef{
    namespace graph{

        typedef struct UserInput{
            bool Pressed_Z=false;
            bool Pressed_Q=false;
            bool Pressed_S=false;
            bool Pressed_D=false;

            bool Pressed_I=false;
            bool Pressed_J=false;
            bool Pressed_K=false;
            bool Pressed_L=false;

            bool Pressed_P=false;
            bool Pressed_M=false;

            bool Close=false;
        } UserInput;

        typedef struct RGBA{
            float R;
            float G;
            float B;
            float A;
        } RGBA_t;

        typedef struct Animation{
            std::string SpriteSheet;

          std::pair<std::size_t,std::size_t> StartPos;
          std::pair<std::size_t,std::size_t> Size;
        } Animation_t;

        typedef struct Particle{
          int posX;
          int posY;
          int velocity;
          float direction;
          int lifeTime;
        } Particle_t;

        typedef struct ParticleEmmiter{
          std::string spriteSheet;
          int posX;
          int posY;

          int density;
          int velocity;
          int lifeTime;

          float scaleX;
          float scaleY;
          float rotation;
          RGBA_t mask;
          std::vector<std::string> objectShaders;
          bool addActive;

          std::vector<Particle_t> particles;
        } ParticleEmmiter_t;

        typedef struct DrawableSprite{
            std::string AnimationName;
            std::size_t CurrentFrame;

            int PosX;
            int PosY;

            float ScaleX;
            float ScaleY;
            float Rotation;
            RGBA_t mask;
        } DrawableSprite_t;

        typedef struct DrawableText{
            std::string Text;
            std::string FontName;
            std::size_t FontSize;

            int PosX;
            int PosY;

            float ScaleX;
            float ScaleY;
            float Rotation;
            float Opacity;
        } DrawableText_t;

        class IDisplayModule{
            public:
                virtual ~IDisplayModule()=default;
                virtual void initialize(std::string assetFolderPath, std::string windowName, std::pair<int,int> windowSize = {1920,1080}) = 0;
                virtual void stop() = 0;
                virtual void clear() = 0;
                virtual void refresh() = 0;
                virtual bool isOpen() = 0;

                virtual void loadAssets(std::string assetFolderPath)=0;
                virtual void storeAssetsPNG(std::string assetPath)=0;
                virtual void storeAssetsWAV(std::string assetPath)=0;
                virtual void storeAssetsTTF(std::string assetPath)=0;
                virtual void storeAssetsSHAD(std::string assetPath)=0;
                virtual void configAssetsAnimations(std::string animationConfigPath)=0;
                virtual void configSettings(std::string settingsConfigPath)=0;

                virtual void drawSprite(std::string animationName, std::size_t currentFrame, int posX, int posY, float scaleX = 1, float scaleY = 1, float rotation = 0, RGBA mask = {1,1,1,1}, std::vector<std::string> objectShaders={"None"}, bool addActive=true) = 0;
                virtual void drawText(std::string textString, std::string fontName, std::size_t fontSize, int posX, int posY, float scaleX = 1, float scaleY = 1, float rotation = 0, RGBA mask = {1,1,1,1}) = 0;
                virtual void drawSpriteHUD(std::string animationName, std::size_t currentFrame, int posX, int posY, float scaleX = 1, float scaleY = 1, float rotation = 0, RGBA mask = {1,1,1,1}, std::vector<std::string> objectShaders={"None"}, bool addActive=true) = 0;
                virtual void drawTextHUD(std::string textString, std::string fontName, std::size_t fontSize, int posX, int posY, float scaleX = 1, float scaleY = 1, float rotation = 0, RGBA mask = {1,1,1,1}) = 0;
                virtual void drawHPBar(zef::graph::HPBar& bar) = 0;

                virtual void playSound(std::string soundName, int volume = 50) = 0;

                virtual void saveAnimation(std::string animationName, std::string spriteSheetName, std::size_t startTileX, std::size_t startTileY, std::size_t tileSizeX, std::size_t tileSizeY) = 0;

                virtual void setActiveShaders(std::vector<std::string> shaderList = {"None"}) = 0;
                virtual std::vector<std::string> getActiveShaders() = 0;

                virtual void addParticleEmmiter(
                    std::string emmiterName, std::string particleSprite,
                    int posX, int posY,
                    int density = 10, int velocity = 4, int lifetime = 1000,
                    float scaleX = 1, float scaleY = 1,
                    float rotation = 0, RGBA mask = {1,1,1,1},
                    std::vector<std::string> objectShaders = {"None"}, bool addActive = true)=0;
                virtual void removeParticleEmmiter(std::string emmiterName) = 0;

                virtual void setCamera(int x, int y, int z) = 0;
                virtual void moveCamera(int x, int y, float z) = 0;

                virtual UserInput getEvent() = 0;
                virtual void updateUserInputs(utils::UserInputs& ui) = 0;
                virtual void updateSettings(std::string SettingName, std::string SettingValue) = 0;

    protected:
    private:
  };



    IDisplayModule* entryPoint();
  } // namespace graph
} // namespace zef

#endif //ENGINE_GRAPHIC_INCLUDES_IDISPLAYMODULE_HPP_
