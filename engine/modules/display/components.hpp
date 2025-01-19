/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** components
*/

#ifndef ENGINE_MODULES_DISPLAY_COMPONENTS_HPP_
#define ENGINE_MODULES_DISPLAY_COMPONENTS_HPP_

#include <map>
#include <utility>
#include <string>
#include "../../Engine.hpp"

namespace zef {
  namespace comp {

    class LobbyCreateTrack {
    public:
      LobbyCreateTrack() {
      }
      int _nbSlots = 3;
      std::string _name = "NewLobby";
      std::string _pwd = "magicarpe";
    };

    class LobbyOffset {
    public:
      LobbyOffset() {
      }
      int offset = -1;
    };

  class MyInfo {
     public:
       MyInfo() {
     }
     bool admin;
     int id;
   };

    class LobbyInfoTrack{
    public:
      LobbyInfoTrack() {
      }
      nlohmann::json j = nlohmann::json::parse("{}");
    };


    class name {
      public:
        name(std::string string) : str(string) {}

      std::string str;
    };
    class drawable {
    public:
      drawable() {
      }

      void addAnimation(const std::string& name, size_t size, size_t freq) {
        _animation_sizes[name] = {size, freq};
      }

      void playAnimation(const std::string& name, float sspeed) {
        current_frame = 0;
        animation     = name;
        speed         = sspeed;
      }

      void playAnimationLoop(const std::string& name, float speed) {
        current_frame        = 0;
        loop_animation       = name;
        loop_animation_speed = speed;
      }

      size_t max_frame_cur() {
        if (animation != "")
          return _animation_sizes[animation].first;
        return _animation_sizes[loop_animation].first;
      }

      size_t getAnimationFreq() {
        if (animation != "") {
          return _animation_sizes[animation].second;
        }
        return _animation_sizes[loop_animation].second;
      }

      float getAnimationSpeed() {
        if (animation != "") {
          return speed;
        }
        return loop_animation_speed;
      }

      void setScale(float x, float y) {
        scaleX = x;
        scaleY = y;
      }

      void setRgba(float r, float g, float b, float a) {
        rgba.R = r;
        rgba.G = g;
        rgba.B = b;
        rgba.A = a;
      }

      zef::graph::RGBA rgba = {1, 1, 1, 1};

      float scaleX = 1.0;
      float scaleY = 1.0;

      size_t current_frame = 0;

      std::string loop_animation = "";
      float loop_animation_speed;

      std::string animation = "";
      float speed;

      int layer;
      size_t timer = 0;

      float rotation = 0.0f;

      std::map<std::string, std::pair<size_t, size_t>> _animation_sizes;
    };

    class drawableText{
      public:
		drawableText(){
		}

        std::string text;
        std::string font;
        int textSize = 42;
        float scaleX = 1.0f;
        float scaleY = 1.0f;
        float rotation = 0.0f;
        zef::graph::RGBA rgba = {1,1,1,1};

        int layer;
    };

  }  // namespace comp

}  // namespace zef

#endif  // ENGINE_MODULES_DISPLAY_COMPONENTS_HPP_
