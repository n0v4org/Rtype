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
    _game  = std::make_unique<Game>();
    _lobby->RegisterLobbyCmd();
    RegisterLaunchGameCmd();
    _game->RegisterGameCmd();
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
      if (room == KO)
        return;
      if (_lobby->bad_room(input, room))
        return;
      player_t temp_player = {};
      bool status          = false;
      for (const auto& room : _lobby->get_lobby()) {
        for (const auto& player : room.players) {
          if (player.id == input.id) {
            status      = true;
            temp_player = player;
          }
        }
      }
      if (!status) {
        _lobby->send_error(input.id, TCP_ERRORS.at(NOT_IN_ROOM).second,
                           TCP_ERRORS.at(NOT_IN_ROOM).first);
        return;
      }
      if (!temp_player.is_admin &&
          _lobby->get_lobby().at(room).owner != DEFAULT_OWNER) {
        _lobby->send_error(input.id, TCP_ERRORS.at(NOT_ADMIN).second,
                           TCP_ERRORS.at(NOT_ADMIN).first);
        return;
      }
      for (const auto& room : _lobby->get_lobby()) {
        for (const auto& player : room.players) {
          if (!player.is_ready) {
            _lobby->send_error(input.id, TCP_ERRORS.at(NOT_READY).second,
                               TCP_ERRORS.at(NOT_READY).first);
            return;
          }
        }
      }
      if (_lobby->get_lobby().at(room).running) {
        _lobby->send_error(input.id, TCP_ERRORS.at(GAME_ALREADY_RUNNING).second,
                           TCP_ERRORS.at(GAME_ALREADY_RUNNING).first);
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
      _game->init_game(players_uuid, tcp_port, udp_port);
    });
  }

  void GameServer::run() {
    _engine.run();
  }

  GameServer::~GameServer() {
  }

}  // namespace rtype