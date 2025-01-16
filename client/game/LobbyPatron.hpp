/*
** EPITECH PROJECT, 2025
** r-type
** File description:
** ButtonPatron
*/

#ifndef LOBBY_PATRON_HPP_
#define LOBBY_PATRON_HPP_

#include <functional>
#include <string>
#include <vector>

#include "Engine.hpp"
#include "modules/controller/components.hpp"
#include "modules/display/components.hpp"
#include "modules/controller/events.hpp"
#include "components.hpp"

class LobbySettings{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self){
    //lobby name
    //lobby password
    //lobby id
    //lobby nb_slots
    //dellobby
    //running
  }
};




class LobbyEmptyPlayerSlot{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y){
    engine.addEntityComponent<zef::comp::position>(self, x, y);

    zef::comp::drawable dr;
    dr.addAnimation("lobbyPlayer1", 1, 200);
    dr.playAnimationLoop("lobbyPlayer1", 1);
    dr.layer = 4;
    dr.setScale(1.4f,1.4f);
    dr.rgba = {0,0,0,1};
    engine.addEntityComponent<zef::comp::drawable>(self, dr);

  }
};

class LobbyOccupiedPlayerSlot{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y, std::string sprite){
    engine.addEntityComponent<zef::comp::position>(self, x, y);

    zef::comp::drawable dr;
    dr.addAnimation(sprite, 1, 200);
    dr.playAnimationLoop(sprite, 1);
    dr.layer = 5;
    dr.setScale(2.4f,2.4f);
    engine.addEntityComponent<zef::comp::drawable>(self, dr);
  }
};
class LobbyPlayerUsername{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y, std::string username){
    engine.addEntityComponent<zef::comp::position>(self, x, y);

    zef::comp::drawableText txt;
    txt.layer = 4;
    txt.text = username;
    txt.font = "eth";
    txt.scaleX = 1.0f;
    txt.scaleY = 1.0f;
    txt.textSize = 24;

    engine.addEntityComponent<zef::comp::drawableText>(self, txt);
  }
};
class LobbyPlayerKick{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y, int id){

  }
};
class LobbyPlayerIsAdmin{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y, bool isAdmin){
    if (!isAdmin)
      return;
    engine.addEntityComponent<zef::comp::position>(self, x, y);

    zef::comp::drawable dr;
    dr.addAnimation("iamadmin", 1, 200);
    dr.playAnimationLoop("iamadmin", 1);
    dr.layer = 6;
    dr.setScale(0.2f,0.2f);
    engine.addEntityComponent<zef::comp::drawable>(self, dr);
  }
};
class LobbyPlayerSetUnsetAdmin{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y, int id, bool isAdmin){

  }
};
class LobbyPlayerIsReady{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y, bool isReady){
    if (!isReady)
      return;
    engine.addEntityComponent<zef::comp::position>(self, x, y);

    zef::comp::drawable dr;
    dr.addAnimation("lobbyPlayer1", 1, 200);
    dr.playAnimationLoop("lobbyPlayer1", 1);
    dr.layer = 4;
    dr.setScale(2.8f,2.8f);
    dr.rgba = {0,1,0,0.6};
    engine.addEntityComponent<zef::comp::drawable>(self, dr);
  }
};

class LobbyPlayerSlot{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self,
                          float x, float y, std::string username,
                          std::string sprite, int id,
                          bool isAdmin, bool isReady, bool amIAdmin){
    if (username != ""){
      engine.instanciatePatron<LobbyOccupiedPlayerSlot>(x,y,sprite);
      engine.instanciatePatron<LobbyPlayerUsername>(x,y + 100,username);
      engine.instanciatePatron<LobbyPlayerIsAdmin>(x + 120,y - 10,isAdmin);
      engine.instanciatePatron<LobbyPlayerIsReady>(x,y,isReady);
      if (amIAdmin){
        engine.instanciatePatron<LobbyPlayerKick>(x,y,id);
        engine.instanciatePatron<LobbyPlayerSetUnsetAdmin>(x,y,id,isAdmin);
      }
    } else {
      engine.instanciatePatron<LobbyEmptyPlayerSlot>(x, y);
    }

  }
};




class LobbyListTabPatronName{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y, std::string lobbyName){

    engine.addEntityComponent<zef::comp::position>(self, x, y);

    zef::comp::drawableText txt;
    txt.layer = 2;
    txt.text = lobbyName;
    txt.font = "eth";
    txt.scaleX = 1.0f;
    txt.scaleY = 1.0f;
    txt.textSize = 20;

    engine.addEntityComponent<zef::comp::drawableText>(self, txt);
  }
};

class LobbyListTabPatronIcon{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y){
    engine.addEntityComponent<zef::comp::position>(self, x, y);

    zef::comp::drawable dr;
    dr.addAnimation("Type_Logo", 1, 200);
    dr.playAnimationLoop("Type_Logo", 1);
    dr.layer = 3;
    dr.setScale(0.3f,0.3f);
    engine.addEntityComponent<zef::comp::drawable>(self, dr);
  }
};

class LobbyListTabPatronEmptySlot{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y){
    engine.addEntityComponent<zef::comp::position>(self, x, y);

    zef::comp::drawable dr;
    std::string lbyplr = "lobbyPlayer"+ std::to_string(rand()%5);
    dr.addAnimation(lbyplr, 1, 200);
    dr.playAnimationLoop(lbyplr, 1);
    dr.layer = 3;
    dr.setScale(0.75f,0.75f);
    dr.rgba = {0,0,0,1};
    engine.addEntityComponent<zef::comp::drawable>(self, dr);
  }
};

class LobbyListTabPatronOccupiedSlot{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y){
    engine.addEntityComponent<zef::comp::position>(self, x, y);

    zef::comp::drawable dr;
    std::string lbyplr = "lobbyPlayer"+ std::to_string(rand()%5);
    dr.addAnimation(lbyplr, 1, 200);
    dr.playAnimationLoop(lbyplr, 1);
    dr.layer = 3;
    dr.setScale(1.0f,1.0f);
    engine.addEntityComponent<zef::comp::drawable>(self, dr);
  }
};


class LobbyListTabPatron {
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self,
                          float x, float y,
                          int LobbyID,
                          std::string lobbyName,
                          int lobbyCapacity, int lobbyPlayers,
                          std::function<void(zef::Engine &, size_t)> onClickCallback){
    engine.addEntityComponent<zef::comp::position>(self, x, y);

    std::vector<zef::utils::hitbox> hb = {zef::utils::hitbox(0, 0, 420, 170)};
    engine.addEntityComponent<zef::comp::clickable>(self, hb);
    zef::comp::event_listener evtl;
    /**/
    evtl.setEvent<zef::evt::LeftclickRelease>(
        [onClickCallback](zef::Engine &engine, size_t self, zef::evt::LeftclickRelease evt) {
            onClickCallback(engine, self);
        }
    );
    engine.addEntityComponent<zef::comp::event_listener>(self, evtl);
    /**/

    zef::comp::drawable dr;
    dr.addAnimation("emptyButton", 1, 200);
    dr.playAnimationLoop("emptyButton", 1);
    dr.layer = 2;
    dr.setScale(1.5f,1.0f);
    engine.addEntityComponent<zef::comp::drawable>(self, dr);


    engine.instanciatePatron<LobbyListTabPatronIcon>(x - 150 ,y - 40);
    engine.instanciatePatron<LobbyListTabPatronName>(x + 100 ,y - 40, lobbyName);
    for (int i = 0; i < lobbyCapacity; i++){
      if (i < lobbyPlayers){
        engine.instanciatePatron<LobbyListTabPatronOccupiedSlot>(x - 175 + i * 100, y + 30 );
      }
      else{
        engine.instanciatePatron<LobbyListTabPatronEmptySlot>(x - 175 + i * 100, y + 30);
      }
    }
  }
};


#endif // LOBBY_PATRON_HPP_
