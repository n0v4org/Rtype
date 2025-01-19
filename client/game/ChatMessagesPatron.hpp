/*
** EPITECH PROJECT, 2025
** r-type
** File description:
** Chat Messages Patron
*/

#ifndef CHAT_MESSAGE_PATRON_HPP_
#define CHAT_MESSAGE_PATRON_HPP_

#include <functional>
#include <string>
#include <vector>

#include "Engine.hpp"
#include "modules/controller/components.hpp"
#include "modules/display/components.hpp"
#include "modules/textzone/components.hpp"
#include "modules/controller/events.hpp"
#include "components.hpp"
#include "ButtonPatron.hpp"
#include "TitlePatron.hpp"



class MsgDel{
public:
  MsgDel(){
  }
};
class MsgZone{
public:
  MsgZone(){
  }
};

class PasswordZone{
public:
  PasswordZone(){
  }
};

class UsrZone{
public:
  UsrZone(){
  }
};

class ChatMsgTrack{
public:
  ChatMsgTrack(){
  }
  std::vector<std::string> _player;
  std::vector<std::string> _message;
};

class ChatMessageTracker{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self){
    engine.addEntityComponent<ChatMsgTrack>(self);
  }
};

class LobbyPasswordEntry{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y){

    engine.addEntityComponent<zef::comp::position>(self, x, y);
    engine.addEntityComponent<zef::comp::textZone>(self);
    engine.addEntityComponent<PasswordZone>(self);

    engine.instanciatePatron<TextButtonPatron>(
        x, y,
        "emptyButton",
        "","eth",42,
        [&](zef::Engine &engine, size_t self) {
          for (auto &&[k,z,t]: ecs::indexed_zipper(engine.reg.get_components<PasswordZone>(), engine.reg.get_components<zef::comp::textZone>())){
            t._focused = !t._focused;
            t._posX = x;
            t._posY = y;
            t._size = 18;
          }
        },
        420.0f, 170.0f, 0.8f, 0.8f, 5
    );

  }
};



class ChatEntry{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y){

    engine.addEntityComponent<zef::comp::position>(self, x, y);
    engine.addEntityComponent<zef::comp::textZone>(self);
    engine.addEntityComponent<MsgZone>(self);

      engine.instanciatePatron<TextButtonPatron>(
          x, y,
          "emptyButton",
          "","eth",42,
          [&](zef::Engine &engine, size_t self) {
            for (auto &&[k,z,t]: ecs::indexed_zipper(engine.reg.get_components<MsgZone>(), engine.reg.get_components<zef::comp::textZone>())){
              t._focused = !t._focused;
              t._posX = x;
              t._posY = y;
              t._size = 24;
            }
          },
          420.0f, 170.0f, 1.0f, 1.0f, 5
      );

  }
};



class UsernameEntry{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y){

    engine.addEntityComponent<zef::comp::position>(self, x, y);
    engine.addEntityComponent<zef::comp::textZone>(self);
    engine.addEntityComponent<UsrZone>(self);

      engine.instanciatePatron<TextButtonPatron>(
          x, y,
          "emptyButton",
          "","eth",25,
          [&](zef::Engine &engine, size_t self) {
            for (auto &&[k,z,t]: ecs::indexed_zipper(engine.reg.get_components<UsrZone>(), engine.reg.get_components<zef::comp::textZone>())){
              t._focused = !t._focused;
              t._posX = x;
              t._posY = y;
              t._size = 15;
            }
          },
          420.0f, 170.0f, 0.6f, 0.6f, 5
      );

  }
};

class WindowMessagePatron{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y){
    engine.addEntityComponent<zef::comp::position>(self, x, y);
    zef::comp::drawable dr;
    dr.addAnimation("Window", 1, 200);
    dr.playAnimationLoop("Window", 1);
    dr.layer = 3;
    dr.setScale(0.6,0.4f);
    engine.addEntityComponent<zef::comp::drawable>(self, dr);

  }
};

class SingleMessagePlayerPatron{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y, int i){
    engine.addEntityComponent<MsgDel>(self);
    engine.addEntityComponent<zef::comp::position>(self, x, y);

    for (auto &&[j,p]: ecs::indexed_zipper(engine.reg.get_components<ChatMsgTrack>())){
      zef::comp::drawableText txt;
      txt.layer = 2;
      txt.text = p._player[i];
      txt.font = "eth";
      txt.scaleX = 1.0f;
      txt.scaleY = 1.0f;
      txt.textSize = 20;
      std::hash<std::string> hashFunction;
      size_t hash = hashFunction(p._player[i]);
      float r = (hash & 0xFF0000) >> 16;
      float g = (hash & 0x00FF00) >> 8;
      float b = (hash & 0x0000FF);
      txt.rgba = {r/200.0f, g/200.0f, b/200.0f, 1.0f};
      engine.addEntityComponent<zef::comp::drawableText>(self, txt);
    }
  }
};
class SingleMessageMessagePatron{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y, int i){
	std::cout << "hey i'm in" << i << std::endl;
    engine.addEntityComponent<MsgDel>(self);
    engine.addEntityComponent<zef::comp::position>(self, x, y);

    for (auto &&[j,p]: ecs::indexed_zipper(engine.reg.get_components<ChatMsgTrack>())){
    zef::comp::drawableText txt;
    txt.layer = 2;
    txt.text = p._message[i];
    txt.font = "eth";
    txt.scaleX = 1.0f;
    txt.scaleY = 1.0f;
    txt.textSize = 20;
    txt.rgba = {.75f,.75f,.75f,1.0f};

    engine.addEntityComponent<zef::comp::drawableText>(self, txt);
    }
  }
};


class ChatMessagesPatron {
public:
    static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y) {
        for (auto &&[i, m] : ecs::indexed_zipper(engine.reg.get_components<ChatMsgTrack>())) {
            int ply = m._player.size();
            for (int j = 0 ; ply - j > ply - 10; j++) {
              if (ply - j - 1 >= 0){
              	engine.instanciatePatron<SingleMessageMessagePatron>(
                  x + 100.f,
                  y + 180.f - ( j * 50.f),
    		      ply - j - 1
                );
                engine.instanciatePatron<SingleMessagePlayerPatron>(
                  x - 150.f,
                  y + 180.f - ( j * 50.f),
                  ply - j -1
                );
              }
            }
        }
    }
};



#endif //CHAT_MESSAGE_PATRON_HPP_



