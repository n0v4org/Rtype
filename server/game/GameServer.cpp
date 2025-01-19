/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** game
*/

#include <vector>
#include <cmath>
#include <sstream>
#include <iostream>
#include <random>
#include <string>
#include <memory>

#include "macro.hpp"
#include "GameServer.hpp"

namespace rtype {

  GameServer::GameServer(int udp_port, int tcp_port) {
    _engine.initServer(udp_port, tcp_port);
    _lobby = std::make_unique<Lobby>(_engine);
    
    _lobby->RegisterLobbyCmd();
    RegisterLaunchGameCmd();
    _engine.addSystem<>(ENGINE_NAME, zef::sys::handle_server);
  }

  int GameServer::generateRandomPort() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1024, 65535);

    return distr(gen);
  }

  void GameServer::RegisterLaunchGameCmd() {
    _engine.registerCommandTcp(LAUNCH_GAME_CMD, [this](zef::Engine& engine,
                                                       input_t input) {
      std::string res = CMD_RES.at(LAUNCH_GAME_CMD).at(SUCCESS);

      if (_lobby->bad_args(input,
                           std::stoi(CMD_RES.at(LAUNCH_GAME_CMD).at(NB_ARGS))))
        return;
      int room = _lobby->get_lobby_id(input);
      
      if (!_lobby->check_start_game(room, input)) {
        return;
      }
      _lobby->set_game_running(room);
      res += _lobby->get_lobby().at(room).name;
      std::vector<std::string> players_uuid;
      int tcp_port = generateRandomPort();
      int udp_port = generateRandomPort();
      json data;
      data["status"]      = std::stoi(CMD_RES.at(LAUNCH_GAME_CMD).at(STATUS));
      data["description"] = res;
      data["room_id"]     = room;
      data["tcp_port"]    = tcp_port;
      data["udp_port"]    = udp_port;
      for (const auto& room : _lobby->get_lobby()) {
        for (const auto& player : room.players) {
          std::string uuid = _lobby->generateFixedLengthString();
          players_uuid.push_back(uuid);
          json player_data           = data;
          player_data["player_uuid"] = uuid;
          _engine.ServerSendTcp(player.id, player_data.dump());
        }
      }

    _games.push_back(std::thread([this, players_uuid, tcp_port, udp_port]() {
        _game  = std::make_unique<Game>();
        _game->launch_game(players_uuid, tcp_port, udp_port);
    }));
    });
  }

  void GameServer::run() {
    _engine.run();
  }

  GameServer::~GameServer() {
  }

}  // namespace rtype