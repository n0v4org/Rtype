/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** Scenes
*/

#ifndef SCENES_HPP_
#define SCENES_HPP_

#include <vector>
#include <iostream>
#include <string>

#include "Engine.hpp"

#include "PlayerPatron.hpp"
#include "AllyPatron.hpp"
#include "BulletPatron.hpp"
#include "EnemyPatron.hpp"
#include "EnemyTurretPatron.hpp"
#include "BackgroundPatron.hpp"
#include "EnemyBulletPatron.hpp"
#include "BlastPatron.hpp"
#include "events.hpp"
#include "EnemyPlanePatron.hpp"
#include "EnemyCrabPatron.hpp"
#include "EnemyRobotPatron.hpp"
#include "BasicWallPatron.hpp"
#include "WaterWallPatron.hpp"
#include "BlockWallPatron.hpp"
#include "BorderPatron.hpp"
#include "BossOnePatron.hpp"
#include "RoomPatron.hpp"
#include "MenuBackgroundPatron.hpp"
#include "ButtonPatron.hpp"
#include "TitlePatron.hpp"
#include "LobbyPatron.hpp"
#include "ChatMessagesPatron.hpp"

class OptionScene;
class MenuScene;
class LobbyScene;
class LobbyListScene;


class LevelScene {
public:
  static void loadScene(zef::Engine& engine, std::vector<size_t> allyId) {
    std::cout << "ùlakenlkeazneazlkneazlkneaz\n";
    engine.addEntityComponent<MoveCamera>(engine.reg.spawn_entity());
    engine.instanciatePatron<PlayerPatron>(0.0f, 0.0f, 0);
    engine.instanciatePatron<BackgroundPatron>(0.0f, 0.0f);
    engine.instanciatePatron<BackgroundPatron>(1920.0f, 0.0f);
    engine.instanciatePatron<BackgroundPatron>(1920.0f * 2, 0.0f);
    engine.instanciatePatron<BackgroundPatron>(1920.0f * 3, 0.0f);
    engine.instanciatePatron<BackgroundPatron>(1920.0f * 4, 0.0f);
    engine.instanciatePatron<BackgroundPatron>(1920.0f * 5, 0.0f);
    engine.instanciatePatron<BackgroundPatron>(1920.0f * 6, 0.0f);
    engine.instanciatePatron<BackgroundPatron>(1920.0f * 7, 0.0f);

    for (auto &i : allyId)
      engine.instanciatePatron<AllyPatron>(0.f, 0.f, i);
  }
};


  struct testNETtest {};

class TestScene {
public:
  static void loadScene(zef::Engine& engine) {
    const ecs::Entity& e = engine.reg.spawn_entity();
    const ecs::Entity& e2 = engine.reg.spawn_entity();
    const ecs::Entity& e3 = engine.reg.spawn_entity();

    zef::comp::event_listener ev;
    ev.setEvent<testNETtest>([](zef::Engine& engine, size_t self, testNETtest t) {
        engine.ClientSendTcp("LAUNCH_GAME");
        //engine.newLoadScene<LevelScene>();
    });
    engine.addEntityComponent<zef::comp::event_listener>(e, ev);
//
    zef::comp::controllable cont;
    cont.bindOnPressed<testNETtest>(zef::utils::Space);
    engine.addEntityComponent<zef::comp::controllable>(e, cont);
  }
};

class TestScene2 {
public:
  static void loadScene(zef::Engine& engine) {
    engine.addEntityComponent<MoveCamera>(engine.reg.spawn_entity());
    engine.instanciatePatron<PlayerPatron>(0.0f, 0.0f, 0);
    engine.instanciatePatron<BackgroundPatron>(0.0f, 0.0f);
    engine.instanciatePatron<BackgroundPatron>(1920.0f, 0.0f);
    engine.instanciatePatron<RoomPatron>("../Assets/config/bossRoomEx.txt", 0.f, 0.f);

  }
};


class LobbyScene{
public:
  static void loadScene(zef::Engine& engine, size_t lobby_id) {
	  engine.registerCommandTcp("204", [](zef::Engine& engine, input_t input) {
    	  nlohmann::json j = nlohmann::json::parse(input.tcp_payload);
    	  int id = j["rooms_id"];
    	  std::string cmd = "GET_LOBBY " + std::to_string(id);
    	  engine.ClientSendTcp(cmd);
  	  });

  engine.registerCommandTcp("202", [](zef::Engine& engine, input_t input) {
    nlohmann::json j = nlohmann::json::parse(input.tcp_payload);
    int id = j["rooms_id"];
    std::string cmd = "GET_LOBBY " + std::to_string(id);
    engine.ClientSendTcp(cmd);
    engine.ClientSendTcp("GET_LOBBY_ID");
  });

  engine.registerCommandTcp("208", [](zef::Engine& engine, input_t input) {
    nlohmann::json j = nlohmann::json::parse(input.tcp_payload);
    int id = j["room_id"];
    std::string cmd = "GET_LOBBY " + std::to_string(id);
    engine.ClientSendTcp(cmd);
  });

  engine.registerCommandTcp("221", [](zef::Engine& engine, input_t input) {
    std::cout << "got 221" << std::endl;
    nlohmann::json j = nlohmann::json::parse(input.tcp_payload);
	std::vector<size_t> ids;
	for (auto &i : j["players"]) {
    ids.push_back(i[1]);
	}
	  engine.newLoadScene<LevelScene>(ids);
  });

  engine.registerCommandTcp("201", [](zef::Engine& engine, input_t input) {
    int  id = 0;
    for (auto &&[i,p]: ecs::indexed_zipper(engine.reg.get_components<zef::comp::LobbyInfoTrack>())){
	  id = p.j["rooms_id"];
    }
	std::string cmd = "GET_LOBBY " + std::to_string(id);
  	engine.ClientSendTcp(cmd);
  });

  engine.registerCommandTcp("210", [](zef::Engine& engine, input_t input) {
    nlohmann::json j = nlohmann::json::parse(input.tcp_payload);
    int id = j["room_id"];
    std::string cmd = "GET_LOBBY " + std::to_string(id);
    engine.ClientSendTcp(cmd);
  });
  engine.registerCommandTcp("213", [](zef::Engine& engine, input_t input) {
    nlohmann::json j = nlohmann::json::parse(input.tcp_payload);
    int id = j["room_id"];
    std::string cmd = "GET_LOBBY " + std::to_string(id);
    engine.ClientSendTcp(cmd);
  });
  engine.registerCommandTcp("214", [](zef::Engine& engine, input_t input) {
    nlohmann::json j =  nlohmann::json::parse(input.tcp_payload);

    for (auto &&[i,p]: ecs::indexed_zipper(engine.reg.get_components<zef::comp::MyInfo>())){
      p.admin = j["is_admin"];
      p.id = j["id"];
    }
  });

  engine.registerCommandTcp("211", [](zef::Engine& engine, input_t input) {
    nlohmann::json j =  nlohmann::json::parse(input.tcp_payload);

    for (auto &&[i,p]: ecs::indexed_zipper(engine.reg.get_components<ChatMsgTrack>())){
      p._player.push_back(j["from"]);
      p._message.push_back(j["message"]);

    }
    for (auto &&[i,p]: ecs::indexed_zipper(engine.reg.get_components<MsgDel>())){
          engine.reg.kill_entity(ecs::Entity(i));
    }

    engine.instanciatePatron<ChatMessagesPatron>(-650.f,60.f);


  });


  engine.registerCommandTcp("203", [](zef::Engine& engine, input_t input) {
      nlohmann::json j = nlohmann::json::parse(input.tcp_payload);
      std::vector<std::pair<int,int>>playerCoords = {{-100.0f, -250.0f},{-150.0f,100.0f},{0.0f,350.0f},{550.0f,0.0f},{400.0f,-300.0f}};
      for (auto &&[i,p]: ecs::indexed_zipper(engine.reg.get_components<PlayerSlot>())){
          engine.reg.kill_entity(ecs::Entity(i));
      }
      for (int i = 0; i < 5; i++) {
          if (i < j["players"].size()){
            engine.instanciatePatron<LobbyPlayerSlot>(playerCoords[i].first,playerCoords[i].second,j["players"][i]["username"],"lobbyPlayer"+std::to_string(i),j["players"][i]["id"],j["players"][i]["is_admin"],j["players"][i]["is_ready"],i);
          }
          else {
            engine.instanciatePatron<LobbyPlayerSlot>(playerCoords[i].first,playerCoords[i].second,"","lobbyPlayer"+std::to_string(i),0,false,false,i);
          }
      }
      engine.instanciatePatron<LobbyNameTag>(j["room_name"]);
      for (auto &&[i,p]: ecs::indexed_zipper(engine.reg.get_components<zef::comp::LobbyInfoTrack>())){
         p.j = j;
      }
  });

    engine.instanciatePatron<MyInfoTracker>();
    engine.instanciatePatron<LobbyInfoTracker>();

    engine.instanciatePatron<MenuBackgroundPatron>();
    engine.instanciatePatron<ButtonPatron>(
        850.0f, -450.0f,
        "returnButton",
        [](zef::Engine &engine, size_t self) {
          engine.ClientSendTcp("QUIT");
          engine.newLoadScene<LobbyListScene>();
        },
        210.0f, 210.0f, 0.5f, 0.5f
    );
    engine.instanciatePatron<TextButtonPatron>(
        550.f, 400.f,
        "emptyButton",
        "READY","eth",72,
        [](zef::Engine &engine, size_t self) {
            engine.fetchEntityComponent<zef::comp::drawable>(self).rgba = {0.5,1,0.5,1};
            engine.fetchEntityComponent<zef::comp::drawableText>(self).rgba = {0,1,0,1};
            engine.ClientSendTcp("SET_PLAYER_READY");
            engine.instanciatePatron<TextButtonPatron>(
				250.f, 400.f,
        		"emptyButton",
        		"LAUNCH GAME","eth",28,
        		[](zef::Engine &engine, size_t self) {
            		engine.ClientSendTcp("LAUNCH_GAME");
        		},
		        420.0f, 170.0f, 0.4f, 0.4f
			);
        },
        420.0f, 170.0f, 1.f, 1.f
    );


    //engine.instanciatePatron<ChatMessagesPatron>(-650.f,60.f);
    engine.instanciatePatron<ChatMessageTracker>();
    engine.instanciatePatron<ChatEntry>(-650.f,400.f);
    engine.instanciatePatron<TextPatron>(-650.f,350.f, "Send Message", "eth",30);
    engine.instanciatePatron<UsernameEntry>(550.f,230.f);
    engine.instanciatePatron<TextPatron>(550.f,190.f, "Change Username", "eth",16);
    engine.instanciatePatron<WindowMessagePatron>(-650.f,00.f);


    std::string cmd = "GET_LOBBY " + std::to_string(lobby_id);
    engine.ClientSendTcp(cmd);

    engine.ClientSendTcp("GET_PLAYER_DATA");

  }
};

class LobbyListScene {
public:
    static void loadScene(zef::Engine& engine) {

        engine.registerCommandTcp("203", [](zef::Engine& engine, input_t input) {
        });
		engine.registerCommandTcp("204", [](zef::Engine& engine, input_t input) {
  	 	});
        engine.registerCommandTcp("202", [](zef::Engine& engine, input_t input) {
  	 	  nlohmann::json j = nlohmann::json::parse(input.tcp_payload);
          int id = j["rooms_id"];
  	 	  engine.newLoadScene<LobbyScene>(id);
        });

        engine.registerCommandTcp("205", [](zef::Engine& engine, input_t input) {
            nlohmann::json j = nlohmann::json::parse(input.tcp_payload);

            for (auto &&[a,b,c]: ecs::indexed_zipper(engine.reg.get_components<zef::comp::textZone>(), engine.reg.get_components<PwdZone>())){
            for (auto &&[k,p]: ecs::indexed_zipper(engine.reg.get_components<zef::comp::LobbyCreateTrack>())){
              int id = j["rooms_id"];
              std::string cmd = "JOIN  " + std::to_string(id) + " " + (b._string != "" ? b._string : "magicarpe");
              engine.ClientSendTcp(cmd);
            }
            }
        });

        engine.registerCommandTcp("200", [&](zef::Engine& engine, input_t input) {
      		nlohmann::json j = nlohmann::json::parse(input.tcp_payload);
            int running_games = 0;
            for (auto &&[k,p]: ecs::indexed_zipper(engine.reg.get_components<zef::comp::LobbyOffset>())){

                for (int i = 0; i < j["rooms"].size(); i++) {
	      	    	if (!j["rooms"][i]["running"]){

                        if (p.offset > 0) {
                          p.offset = 0;
                        }
                        if (p.offset * -1 > j["rooms"].size() - 1) {
                          p.offset = j["rooms"].size() - 1;
                          p.offset *= -1 ;
                        }
                        if (j["rooms"].size() - i + p.offset - running_games >=0 && j["rooms"].size() - i + p.offset - running_games <= 2){
      		    		    engine.instanciatePatron<LobbyListTabPatron>(
         	      		    -575.0f, -80.0f + ((j["rooms"].size() - i + p.offset - running_games) * 200.0f),
                  		    j["rooms"][i]["rooms_id"], j["rooms"][i]["room_name"],
                  		    j["rooms"][i]["slot"], j["rooms"][i]["players"].size(),
                  		    [j,i](zef::Engine &engine, size_t self) {
                      	        int id = j["rooms"][i]["rooms_id"];
                      	    	std::string s= "JOIN " + std::to_string(id) + " magicarpe";
                      	    	engine.ClientSendTcp(s);
                  		    }
                  		    );
                        }
          	    	} else {
                      running_games += 1;
                    }
                }
            }
  		});
    	engine.instanciatePatron<MenuBackgroundPatron>();
        engine.instanciatePatron<LobbyOffsetTracker>();
        engine.instanciatePatron<ButtonPatron>(
            850.0f, -450.0f,
            "returnButton",
            [](zef::Engine &engine, size_t self) {
                engine.newLoadScene<MenuScene>();
            },
            210.0f, 210.0f, 0.5f, 0.5f
        );
        engine.instanciatePatron<TextButtonPatron>(
            -550.f,-400.f,
            "emptyButton",
            "Lobby List","eth",42,
            [](zef::Engine &engine, size_t self) {
            },
            420.0f, 170.0f, 1.f, 1.f
        );
        engine.instanciatePatron<TitlePatron>(
            -550.0f, 100.0f,
            "Window",
            0.8f, 0.5f
        );

        engine.instanciatePatron<ButtonPatron>(
            -175.0f, 100.0f,
            "Forward_BTN",
            [](zef::Engine &engine, size_t self) {
                for (auto &&[i,p]: ecs::indexed_zipper(engine.reg.get_components<Tab>())){
                    engine.reg.kill_entity(ecs::Entity(i));
                }
                for (auto &&[i,p]: ecs::indexed_zipper(engine.reg.get_components<zef::comp::LobbyOffset>())){
                   p.offset == 0;
                }
                engine.ClientSendTcp("GET_ALL_LOBBY");
            },
            210.0f, 210.0f, 0.5f, 0.5f, 180.0f
        );

		engine.instanciatePatron<ButtonPatron>(
            -175.0f, -50.0f,
            "Forward_BTN",
            [](zef::Engine &engine, size_t self) {
                for (auto &&[i,p]: ecs::indexed_zipper(engine.reg.get_components<Tab>())){
                    engine.reg.kill_entity(ecs::Entity(i));
                }
                for (auto &&[i,p]: ecs::indexed_zipper(engine.reg.get_components<zef::comp::LobbyOffset>())){
                   p.offset += 1;
                }
                engine.ClientSendTcp("GET_ALL_LOBBY");
            },
            210.0f, 210.0f, 0.5f, 0.5f, 270.0f
        );

    	engine.instanciatePatron<ButtonPatron>(
            -175.0f, 250.0f,
            "Forward_BTN",
            [](zef::Engine &engine, size_t self) {
                for (auto &&[i,p]: ecs::indexed_zipper(engine.reg.get_components<Tab>())){
                    engine.reg.kill_entity(ecs::Entity(i));
                }
                for (auto &&[i,p]: ecs::indexed_zipper(engine.reg.get_components<zef::comp::LobbyOffset>())){
                   p.offset -= 1;
                }
                engine.ClientSendTcp("GET_ALL_LOBBY");
            },
            210.0f, 210.0f, 0.5f, 0.5f, 90.0f
        );

        engine.instanciatePatron<LobbyCreatePatron>(350.f,-100.f);


        engine.ClientSendTcp("GET_ALL_LOBBY");
    }
};

class MenuScene {
public:
    static void loadScene(zef::Engine &engine) {
        engine.instanciatePatron<MenuBackgroundPatron>();

        engine.instanciatePatron<TitlePatron>(
            0.0f, -250.0f,
            "Type_Logo",
            1.5f, 1.5f
        );

        engine.instanciatePatron<ButtonPatron>(
            0.0f, 100.0f,
            "Start",
            [](zef::Engine &engine, size_t self) {
                engine.newLoadScene<LobbyListScene>();
            },
            410.0f, 121.0f
        );

        engine.instanciatePatron<ButtonPatron>(
            0.0f, 300.0f,
            "Exit",
            [](zef::Engine &engine, size_t self) {
                std::cout << "Quit clicked!" << std::endl;
            },
            410.0f, 121.0f
        );

        engine.instanciatePatron<ButtonPatron>(
            850.0f, -450.0f,
            "Settings",
            [](zef::Engine &engine, size_t self) {
                engine.newLoadScene<OptionScene>();
            },
            210.0f, 210.0f, 0.5f, 0.5f
        );
    }
};

class OptionScene {
public:
    static void loadScene(zef::Engine &engine) {
        engine.instanciatePatron<MenuBackgroundPatron>();

        engine.instanciatePatron<ButtonPatron>(
            -850.0f, -450.0f,
            "Backward_BTN",
            [](zef::Engine &engine, size_t self) {
                engine.newLoadScene<MenuScene>();
            },
            210.0f, 210.0f, 0.5f, 0.5f
        );

        engine.instanciatePatron<TitlePatron>(
            0.0f, 0.0f,
            "Window",
            1.0f, 0.70f
        );

        engine.instanciatePatron<TitlePatron>(
            0.0f, -440.0f,
            "Information",
            1.0f, 0.8f, 1
        );

        engine.instanciatePatron<ButtonPatron>(
            0.0f, -200.0f,
            "Sound_BTN",
            [](zef::Engine &engine, size_t self) {
                std::string vol = "Volume";
                int currentVolume = std::stoi(engine.GraphLib->getSetting(vol).c_str());
                engine.GraphLib->playSound("checkSound");
            },
            210.0f, 210.0f, 0.75f, 0.75f
        );

        engine.instanciatePatron<ButtonPatron>(
            -250.0f, -200.0f,
            "Backward_BTN",
            [](zef::Engine &engine, size_t self) {
                std::string vol = "Volume";
                int currentVolume = std::stoi(engine.GraphLib->getSetting(vol).c_str());
                int newVolume;
                if (currentVolume <= 0) {
                    newVolume = 0;
                } else {
                    newVolume = currentVolume - 5;
                    engine.GraphLib->playSound("checkSound");
                }
                engine.GraphLib->updateSettings("Volume", std::to_string(newVolume));
            },
            210.0f, 210.0f, 0.75f, 0.75f
        );

        engine.instanciatePatron<ButtonPatron>(
            250.0f, -200.0f,
            "Forward_BTN",
            [](zef::Engine &engine, size_t self) {
                std::string vol = "Volume";
                int currentVolume = std::stoi(engine.GraphLib->getSetting(vol).c_str());
                int newVolume;
                if (currentVolume >= 100) {
                    newVolume = 100;
                } else {
                    newVolume = currentVolume + 5;
                    engine.GraphLib->playSound("checkSound");
                }
                engine.GraphLib->updateSettings("Volume", std::to_string(newVolume));
            },
            210.0f, 210.0f, 0.75f, 0.75f
        );

        engine.instanciatePatron<SoundBarPatron>(
            0.0f, -50.0f
        );
    }
};

#endif /* !SCENES_HPP_ */
