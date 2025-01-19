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
#include "modules/textzone/components.hpp"
#include "modules/controller/events.hpp"
#include "components.hpp"
#include "ButtonPatron.hpp"
#include "TitlePatron.hpp"

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


class LobbyInfoTracker{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self){
    engine.addEntityComponent<zef::comp::LobbyInfoTrack>(self);
  }
};

class LobbyOffsetTracker{
  public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self){
    engine.addEntityComponent<zef::comp::LobbyOffset>(self);
    }
};

class LobbyCreateTracker{
  public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self){
    engine.addEntityComponent<zef::comp::LobbyCreateTrack>(self);
    }
};

//UWU  class MyInfoTracker{
//UWU    public:
//UWU    static void instanciate(zef::Engine &engine, const ecs::Entity &self){
//UWU      engine.addEntityComponent<zef::comp::MyInfo>(self);
//UWU      }
//UWU  };

class PlayerSlot{
public:
  PlayerSlot() {
  }
};
class PlayerKickAdminWindow{
public:
  PlayerKickAdminWindow() {
  }
};

class LobbyEmptyPlayerSlot{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y){
    engine.addEntityComponent<PlayerSlot>(self);
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


class LobbyNameTag{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, std::string name){
    engine.addEntityComponent<PlayerSlot>(self);
    engine.addEntityComponent<zef::comp::position>(self, -650.0f, -400.0f);
    engine.instanciatePatron<TextButtonPatron>(
        -650.f,-400.f,
        "emptyButton",
        name,"eth",42,
        [](zef::Engine &engine, size_t self) {
        },
        420.0f, 170.0f, 1.f, 1.f
      );
  }
};




class LobbyPlayerKickAdminPatronWindow{
public:
    static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y){
      engine.addEntityComponent<PlayerKickAdminWindow>(self);
      engine.addEntityComponent<zef::comp::position>(self, x, y);

      zef::comp::drawable dr;
      dr.addAnimation("window", 1, 200);
      dr.playAnimationLoop("window", 1);
      dr.layer = 2;
      dr.setScale(0.2f,0.3f);
      engine.addEntityComponent<zef::comp::drawable>(self, dr);
  }
};
class LobbyPlayerKickAdminPatronKick{
public:
};
class LobbyPlayerKickAdminPatronAdmin{
public:
};
class LobbyPlayerKickAdminPatronExit{
public:
};


class LobbyPlayerKickAdminPatron{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y, int slotId){
    engine.addEntityComponent<PlayerKickAdminWindow>(self);
    for (auto &&[k,p]: ecs::indexed_zipper(engine.reg.get_components<zef::comp::LobbyInfoTrack>())){
      for (auto &&[l,m]: ecs::indexed_zipper(engine.reg.get_components<zef::comp::MyInfo>())){
        if (m.admin){
            engine.instanciatePatron<LobbyPlayerKickAdminPatronButton>(x, y, "Window", " ", "eth", 42, [](zef::Engine &engine, size_t self){}, 940.f, 1400.f,0.3f,0.25f,2,0.f);

           int id = p.j["players"][slotId]["id"];
            int permission = (p.j["players"][slotId]["is_admin"] ? 0 : 1);
            std::string cmdadmin = "UPDATE_PERM " + std::to_string(id) + " " + std::to_string(permission);
            std::string cmdkick = "KICK_PLAYER " + std::to_string(id);

            engine.instanciatePatron<LobbyPlayerKickAdminPatronButton>(
              x + 100.f, y + 200.0f,
              "EmptyButton",
              "Admin"/* + p.j["players"][slotId]["username"]*/,"eth",42,
              [cmdadmin](zef::Engine &engine, size_t self) {
                engine.ClientSendTcp(cmdadmin);
              },
              420.0f, 170.0f, 0.3f, 0.3f, 8, 0.f
            );
            engine.instanciatePatron<LobbyPlayerKickAdminPatronButton>(
              x - 100.0f, y + 200.0f,
              "EmptyButton",
              "Kick"/* + p.j["players"][slotId]["username"]*/,"eth",42,
              [cmdkick](zef::Engine &engine, size_t self) {
                engine.ClientSendTcp(cmdkick);
              },
              420.0f, 170.0f, 0.3f, 0.3f,8, 0.f
            );
            engine.instanciatePatron<LobbyPlayerKickAdminPatronButton>(
              x + 0.f, y + 200.0f,
              "Forward_BTN", " " , "eth", 42,
              [](zef::Engine &engine, size_t self) {
                for (auto &&[k,p]: ecs::indexed_zipper(engine.reg.get_components<PlayerKickAdminWindow>())){
                  engine.reg.kill_entity(ecs::Entity(k));
                }
              },
                      100.0f, 100.0f, 0.4f, 0.4f, 5,  270.f
            );
        }
      }
//UWU      }
//    }
  }
};


class LobbyOccupiedPlayerSlot{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y, std::string sprite, int slotId){
    engine.addEntityComponent<PlayerSlot>(self);

    /**/
        engine.addEntityComponent<zef::comp::position>(self, x, y);
        std::function<void(zef::Engine &, size_t)> onClickCallback =
            [x,y,slotId](zef::Engine &engine, size_t self) {
            engine.instanciatePatron<LobbyPlayerKickAdminPatron>(x,y,slotId);
            };

        std::vector<zef::utils::hitbox> hb = {zef::utils::hitbox(0, 0, 100.f * 2.4f, 50.f * 2.4f)};
        engine.addEntityComponent<zef::comp::clickable>(self, hb);

        zef::comp::event_listener evtl;
        evtl.setEvent<zef::evt::LeftclickRelease>(
            [onClickCallback](zef::Engine &engine, size_t self, zef::evt::LeftclickRelease evt) {
                onClickCallback(engine, self);
            }
        );
        engine.addEntityComponent<zef::comp::event_listener>(self, evtl);

        zef::comp::drawable dr;
        dr.addAnimation(sprite, 1, 200);
        dr.playAnimationLoop(sprite, 1);
        dr.layer = 5;
        dr.setScale(2.4f,2.4f);
        engine.addEntityComponent<zef::comp::drawable>(self, dr);
    }
    /**/
};

class LobbyPlayerUsername{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y, std::string username){
    engine.addEntityComponent<PlayerSlot>(self);
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

class LobbyPlayerIsAdmin{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y, bool isAdmin){
    engine.addEntityComponent<PlayerSlot>(self);
    engine.addEntityComponent<zef::comp::position>(self, x, y);
    if (!isAdmin)
      return;

    zef::comp::drawable dr;
    dr.addAnimation("iamadmin", 1, 200);
    dr.playAnimationLoop("iamadmin", 1);
    dr.layer = 6;
    dr.setScale(0.2f,0.2f);
    engine.addEntityComponent<zef::comp::drawable>(self, dr);
  }
};

class LobbyPlayerKick{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y, int id){
    engine.addEntityComponent<PlayerKickAdminWindow>(self);
    engine.addEntityComponent<zef::comp::position>(self, x, y);
  }
};
class LobbyPlayerSetUnsetAdmin{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y, int id, bool isAdmin){
    engine.addEntityComponent<PlayerKickAdminWindow>(self);
    engine.addEntityComponent<zef::comp::position>(self, x, y);

  }
};

class LobbyPlayerIsReady{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y, bool isReady){
    engine.addEntityComponent<PlayerSlot>(self);
    engine.addEntityComponent<zef::comp::position>(self, x, y);
    if (!isReady)
      return;

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
                          bool isAdmin, bool isReady, int slotId){
    engine.addEntityComponent<PlayerSlot>(self);
    if (username != ""){
      engine.instanciatePatron<LobbyOccupiedPlayerSlot>(x,y,sprite,slotId);
      engine.instanciatePatron<LobbyPlayerUsername>(x,y + 100,username);
      engine.instanciatePatron<LobbyPlayerIsAdmin>(x + 120,y - 10,isAdmin);
      engine.instanciatePatron<LobbyPlayerIsReady>(x,y,isReady);
    } else {
      engine.instanciatePatron<LobbyEmptyPlayerSlot>(x, y);
    }
  }
};


class Tab{
public:
  Tab() {
  }
};

class LobbyListTabPatronName{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y, std::string lobbyName){
    engine.addEntityComponent<Tab>(self);
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
    engine.addEntityComponent<Tab>(self);
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
    engine.addEntityComponent<Tab>(self);
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
    engine.addEntityComponent<Tab>(self);
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
    engine.addEntityComponent<Tab>(self);
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


class LobbyCreateWindow{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y){
    engine.addEntityComponent<zef::comp::position>(self, x, y);
    zef::comp::drawable dr;
    dr.addAnimation("Window", 1, 200);
    dr.playAnimationLoop("Window", 1);
    dr.layer = 3;
    dr.setScale(0.8f,0.5f);
    engine.addEntityComponent<zef::comp::drawable>(self, dr);
  }
};
class LobbyCreateNameTitle{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y){

    engine.addEntityComponent<zef::comp::position>(self, x, y);

    zef::comp::drawableText txt;
    txt.layer = 4;
    txt.text = "Lobby Name";
    txt.font = "eth";
    txt.scaleX = 1.0f;
    txt.scaleY = 1.0f;
    txt.textSize = 24;
    engine.addEntityComponent<zef::comp::drawableText>(self, txt);
  }
};
class LobbyCreateName{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y){

    engine.addEntityComponent<zef::comp::position>(self, x, y);

    for (auto &&[k,p]: ecs::indexed_zipper(engine.reg.get_components<zef::comp::LobbyCreateTrack>())){
        engine.instanciatePatron<TextButtonPatron>(
            x, y,
            "emptyButton",
            p._name,"eth",42,
            [](zef::Engine &engine, size_t self) {

            },
            420.0f, 170.0f, 1.f, 1.f, 5
        );
  }

  }
};
class LobbyCreateSlotsTitle{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y){
  }
};

class SlotRedo{
  public:
    SlotRedo(){
    }
};

class LobbyCreateSlotFull{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y){
    engine.addEntityComponent<SlotRedo>(self);
    engine.addEntityComponent<zef::comp::position>(self, x, y);
    zef::comp::drawable dr;
    dr.addAnimation("Slot", 1, 200);
    dr.playAnimationLoop("Slot", 1);
    dr.layer = 4;
    dr.setScale(0.1,0.1f);
    dr.rotation = 90.0f;
    engine.addEntityComponent<zef::comp::drawable>(self, dr);

  }
};
class LobbyCreateSlotEmpty{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y){
    engine.addEntityComponent<SlotRedo>(self);
    engine.addEntityComponent<zef::comp::position>(self, x, y);
    zef::comp::drawable dr;
    dr.addAnimation("Slot", 1, 200);
    dr.playAnimationLoop("Slot", 1);
    dr.layer = 4;
    dr.setScale(0.08,0.08f);
    dr.rotation = 90.0f;
    dr.rgba = {0.2,0.2,0.2,1};
    engine.addEntityComponent<zef::comp::drawable>(self, dr);
  }
};

class LobbyCreatePasswordTitle{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y){

    engine.addEntityComponent<zef::comp::position>(self, x, y);

    zef::comp::drawableText txt;
    txt.layer = 4;
    txt.text = "Lobby Password";
    txt.font = "eth";
    txt.scaleX = 1.0f;
    txt.scaleY = 1.0f;
    txt.textSize = 24;
    engine.addEntityComponent<zef::comp::drawableText>(self, txt);
  }
};
class LobbyCreatePassword{
public:
  static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y){
    engine.addEntityComponent<zef::comp::position>(self, x, y);

    for (auto &&[k,p]: ecs::indexed_zipper(engine.reg.get_components<zef::comp::LobbyCreateTrack>())){
        engine.instanciatePatron<TextButtonPatron>(
            x, y,
            "emptyButton",
            p._pwd,"eth",42,
            [](zef::Engine &engine, size_t self) {
            },
            420.0f, 170.0f, 1.f, 1.f, 5
        );
    }
  }
};

class LobbyCreatePatron{
  public:
    static void instanciate(zef::Engine &engine, const ecs::Entity &self, float x, float y){
      std::cout << "miam le patron" << std::endl;
      engine.instanciatePatron<LobbyCreateTracker>();
      std::cout << "webedia" << std::endl;

      engine.instanciatePatron<LobbyCreateWindow>(x, y);
      engine.instanciatePatron<LobbyCreateTitle>(x, y + 500.0f);
      engine.instanciatePatron<LobbyCreateNameTitle>(x, y -250.0f);
      engine.instanciatePatron<LobbyCreateName>(x, y - 200.0f);
      std::cout << "l'entreprise familiale a été reprise par ma tante" << std::endl;
      engine.instanciatePatron<LobbyCreateSlotsTitle>(x, y - 100.0f);
      for (auto &&[k,p]: ecs::indexed_zipper(engine.reg.get_components<zef::comp::LobbyCreateTrack>())){
        for (int i = 0; i < 5; i ++){
          if (i < p._nbSlots) {
            engine.instanciatePatron<LobbyCreateSlotFull>(x - 80.f + (i * 40.f), y);
          } else {
            engine.instanciatePatron<LobbyCreateSlotEmpty>(x - 80.f + (i * 40.f), y);
          }
        }
      }
      std::cout << "l'entreprise familiale a été reprise par ma tante" << std::endl;

      engine.instanciatePatron<ButtonPatron>(
        x + 180.0f, y,
        "Forward_BTN",
        [x,y](zef::Engine &engine, size_t self) {
          for (auto &&[i,p]: ecs::indexed_zipper(engine.reg.get_components<zef::comp::LobbyCreateTrack>())){
            p._nbSlots += 1;
          }
          for (auto &&[k,p]: ecs::indexed_zipper(engine.reg.get_components<SlotRedo>())){
                    engine.reg.kill_entity(ecs::Entity(k));
          }
          for (auto &&[k,p]: ecs::indexed_zipper(engine.reg.get_components<zef::comp::LobbyCreateTrack>())){
            for (int i = 0; i < 5; i ++){
              if (i < p._nbSlots) {
                engine.instanciatePatron<LobbyCreateSlotFull>(x - 80.f + (i * 40.f), y);
              } else {
                engine.instanciatePatron<LobbyCreateSlotEmpty>(x - 80.f + (i * 40.f), y);
              }
            }
          }
        },
        210.0f, 210.0f, 0.5f, 0.5f, 0.0f, 4
      );
      std::cout << "l'entreprise familiale a été reprise par ma tante" << std::endl;

      engine.instanciatePatron<ButtonPatron>(
        x - 180.0f, y,
        "Forward_BTN",
        [x,y](zef::Engine &engine, size_t self) {
          for (auto &&[i,p]: ecs::indexed_zipper(engine.reg.get_components<zef::comp::LobbyCreateTrack>())){
            p._nbSlots -= 1;
          }
          for (auto &&[k,p]: ecs::indexed_zipper(engine.reg.get_components<SlotRedo>())){
            engine.reg.kill_entity(ecs::Entity(k));
          }
          for (auto &&[k,p]: ecs::indexed_zipper(engine.reg.get_components<zef::comp::LobbyCreateTrack>())){
            for (int i = 0; i < 5; i ++){
              if (i < p._nbSlots) {
                engine.instanciatePatron<LobbyCreateSlotFull>(x - 80.f + (i * 40.f), y);
              } else {
                engine.instanciatePatron<LobbyCreateSlotEmpty>(x - 80.f + (i * 40.f), y);
              }
            }
          }
        },
        210.0f, 210.0f, 0.5f, 0.5f, 180.0f, 4
      );
      std::cout << "l'entreprise familiale a été reprise par ma tante" << std::endl;
      engine.instanciatePatron<LobbyCreatePasswordTitle>(x, y + 150.0f);
      engine.instanciatePatron<LobbyCreatePassword>(x, y + 200.0f );
      std::cout << "l'entreprise familiale a été reprise par le chien (frédérique le chientre de jonfre)" << std::endl;

    }

};

#endif // LOBBY_PATRON_HPP_
