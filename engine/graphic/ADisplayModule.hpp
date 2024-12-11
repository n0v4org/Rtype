/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** IDisplayModule
*/

#ifndef CLIENT_INCLUDE_GRAPHIC_ADISPLAYMODULE_HPP_
#define CLIENT_INCLUDE_GRAPHIC_ADISPLAYMODULE_HPP_

#include "./IDisplayModule.hpp"

namespace zef {
    namespace graph {

template<typename PNG, typename WAV, typename TTF, typename VERT>
class ADisplayModule : public IDisplayModule{
  public:
    ADisplayModule()=default;
    virtual ~ADisplayModule()=default;
    virtual void initialize(std::string) = 0;
    virtual void stop() = 0;
    virtual void clear() = 0;
    virtual void refresh() = 0;
    virtual bool isOpen() = 0;


    void loadAssets(std::string folder_path) override{
      std::string pathname;
      std::string folder_name;
      bool status = false;
      if (std::filesystem::exists(folder_path + "/sprites")) {
        for (const auto &i: std::filesystem::directory_iterator(folder_path + "/sprites")) {
          for (auto &[key, data]: _sprites) {
            if (key == folder_path) {
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
      if (std::filesystem::exists(folder_path + "/fonts")) {
        for (const auto &i: std::filesystem::directory_iterator(folder_path + "/fonts")) {
          for (auto &[key, data]: _fonts) {
            if (key == folder_path) {
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
      if (std::filesystem::exists(folder_path + "/sounds")) {
        for (const auto &i: std::filesystem::directory_iterator(folder_path + "/sounds")) {
          for (auto &[key, data]: _sounds) {
            if (key == folder_path) {
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
      if (std::filesystem::exists(folder_path + "/shaders")) {
        for (const auto &i: std::filesystem::directory_iterator(folder_path + "/shaders")) {
          for (auto &[key, data]: _shaders) {
            if (key == folder_path) {
              status = true;
            }
          }
          if (status) {
            break;
          }
          storeAssetsVERT(i.path());
        }
      }
    };
    virtual void storeAssetsPNG(std::string)=0;
    virtual void storeAssetsWAV(std::string)=0;
    virtual void storeAssetsTTF(std::string)=0;
    virtual void storeAssetsVERT(std::string)=0;

    virtual UserInput getEvent() = 0;

    //virtual void drawSprite(DrawableSprite_t) = 0;
    virtual void drawSprite(std::string, std::size_t, int, int, float, float, float, float) = 0;
    //virtual void drawText(DrawableText_t) = 0;
    virtual void drawText(std::string, std::string, std::size_t, int, int, float, float, float, float) = 0;

    virtual void playSound(std::string) = 0;

    //virtual void saveAnimation(std::string, Animation_t)=0;
    virtual void saveAnimation(std::string, std::string, std::size_t, std::size_t, std::size_t, std::size_t) = 0;

    virtual void setCamera(int,int,int)=0;
    virtual void moveCamera(int,int,int)=0;

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