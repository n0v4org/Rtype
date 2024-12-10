/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** ADisplayModule
*/

#ifndef CLIENT_INCLUDE_GRAPHIC_ADISPLAYMODULE_HPP_
#define CLIENT_INCLUDE_GRAPHIC_ADISPLAYMODULE_HPP_

#include "./IDisplayModule.hpp"

namespace rtype{

template<typename PNG, typename WAV, typename TTF, typename VERT>
class ADisplayModule : IDisplayModule{
  public:
    ADisplayModule()=default;
    ~ADisplayModule()=default;
    virtual void initialize(std::string) = 0;
    virtual void stop() = 0;
    virtual void clear() = 0;
    virtual void refresh() = 0;
    virtual bool isOpen() = 0;

    void loadAssets(std::string folder_path) override
    {
    	std::string pathname;
      	std::string folder_name;

       	bool status = false;
        for (const auto &i: std::filesystem::directory_iterator(folder_path + "/sprites")) {
          for (auto &[key, data]: _sprites) {
            if (key == folder_path) {
              status = true;
            }
          }
          if (status) {
            break;
          }
          pathname = i.path();
          folder_name = pathname.substr(pathname.find("sprites/") + 4);
            storeAssetsPNG(pathname);
          }
          status = false;
          for (const auto &i: std::filesystem::directory_iterator(folder_path + "/fonts")) {
            for (auto &[key, data]: _fonts) {
              if (key == folder_path) {
                status = true;
              }
            }
            if (status) {
              break;
            }
            pathname =  i.path();
            folder_name = pathname.substr(pathname.find("fonts/") + 6);
            storeAssetsTTF(i.path());
          }
          status = false;
          for (const auto &i: std::filesystem::directory_iterator(folder_path + "/sounds")) {
            for (auto &[key, data]: _sounds) {
              if (key == folder_path) {
                status = true;
              }
            }
            if (status) {
              break;
            }
            pathname =  i.path();
            folder_name = pathname.substr(pathname.find("sounds/") + 6);
            storeAssetsWAV(i.path());
          }
          status = false;
          for (const auto &i: std::filesystem::directory_iterator(folder_path + "/shaders")) {
            for (auto &[key, data]: _shaders) {
              if (key == folder_path) {
                status = true;
              }
            }
            if (status) {
              break;
            }
            pathname =  i.path();
            folder_name = pathname.substr(pathname.find("shaders/") + 6);
            storeAssetsVERT(i.path());
          }
        };
    virtual void storeAssetsPNG(std::string)=0;
    virtual void storeAssetsWAV(std::string)=0;
    virtual void storeAssetsTTF(std::string)=0;
    virtual void storeAssetsVERT(std::string)=0;

    virtual Event_t getEvent() = 0;

    virtual void playSound(std::string) = 0;
    virtual void drawText() = 0;
    virtual void drawSprite() = 0;

    virtual void saveAnimation(std::pair<std::size_t,std::size_t>,std::pair<std::size_t,std::size_t>,float,std::chrono::milliseconds)=0;

    virtual void playOnce(std::string,std::string)=0;
    virtual void playLoop(std::string,std::string)=0;

    virtual void setAnimationSpeed(std::string,float)=0;
    virtual void setScale(std::string,std::pair<float,float>)=0;
    virtual void setPosition(std::string,std::pair<std::size_t,std::size_t>)=0;
    virtual void setRotation(std::string,float)=0;

    virtual void moveCamera(std::vector<float>)=0;

  protected:
  private:
    std::map<std::string,Entity_t> _entities;
    std::map<std::string,Animation_t> _animations;
    std::map<std::string, std::pair<std::string,std::string>> _texts;

    std::map<std::string,PNG> _sprites;
    std::map<std::string,WAV> _sounds;
    std::map<std::string,TTF> _fonts;
    std::map<std::string,VERT> _shaders;

};
}

#endif //CLIENT_INCLUDE_GRAPHIC_ADISPLAYMODULE_HPP_