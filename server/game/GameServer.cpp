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

#include "GameServer.hpp"

namespace rtype {

  GameServer::GameServer(int udp_port, int tcp_port) {
    _engine.initServer(udp_port, tcp_port);
    _lobby = std::make_unique<Lobby>(_engine);
    _game = std::make_unique<Game>(_engine);
    _lobby->RegisterLobbyCmd();
    RegisterLaunchGameCmd();
    _game->RegisterGameCmd();
    _engine.addSystem<>(ENGINE_NAME, zef::sys::handle_server);
  }

  void GameServer::RegisterLaunchGameCmd() {
     _engine.registerCommandTcp(LAUNCH_GAME_CMD, [this](zef::Engine& engine,
                                                       input_t input) {
      std::string res = CMD_RES.at(LAUNCH_GAME_CMD).at(SUCCESS);

      if (_lobby->bad_args(input, std::stoi(CMD_RES.at(LAUNCH_GAME_CMD).at(NB_ARGS))) ||
          !_lobby->is_number(input.tcp_payload, input.id))
        return;
      int room = std::stoi(input.tcp_payload);
      if (_lobby->bad_room(input, room))
        return;
      std::vector<player_t>::iterator it = std::find_if(
          _lobby->get_lobby().at(room).players.begin(), _lobby->get_lobby().at(room).players.end(),
          [input](const player_t& player) { return player.id == input.id; });
      if (it == _lobby->get_lobby().at(room).players.end()) {
        _lobby->send_error(input.id, TCP_ERRORS.at(NOT_IN_ROOM).second,
                   TCP_ERRORS.at(NOT_IN_ROOM).first);
        return;
      }
      if (!(*it).is_admin && _lobby->get_lobby().at(room).owner != DEFAULT_OWNER) {
        _lobby->send_error(input.id, TCP_ERRORS.at(NOT_ADMIN).second,
                   TCP_ERRORS.at(NOT_ADMIN).first);
        return;
      }
      it = std::find_if(
          _lobby->get_lobby().at(room).players.begin(), _lobby->get_lobby().at(room).players.end(),
          [](const player_t& player) { return !player.is_ready; });
      if (it != _lobby->get_lobby().at(room).players.end()) {
        _lobby->send_error(input.id, TCP_ERRORS.at(NOT_READY).second,
                   TCP_ERRORS.at(NOT_READY).first);
        return;
      }
      if (_lobby->get_lobby().at(room).running) {
         _lobby->send_error(input.id, TCP_ERRORS.at(GAME_ALREADY_RUNNING).second,
                   TCP_ERRORS.at(GAME_ALREADY_RUNNING).first);
          return;
      }
      _lobby->set_game_running(room);
      res += _lobby->get_lobby().at(room).name;
      std::vector<std::string> players_uuid;
      json data;
      data["status"]      = std::stoi(CMD_RES.at(QUIT_ROOM_CMD).at(STATUS));
      data["description"] = res;
      data["room_id"]     = room;
      for (const auto& room : _lobby->get_lobby()) {
        for (const auto& player : room.players) {
          std::string uuid = _lobby->generateFixedLengthString();
          players_uuid.push_back(uuid);
          json player_data = data;
          player_data["player_uuid"] = uuid;
          _engine.ServerSendTcp(player.id, player_data.dump());
        }
      }
      _game->init_game(players_uuid);
    });
  }

  void GameServer::run() {
    _engine.run();
  }

  GameServer::~GameServer() {
  }

}  // namespace rtype