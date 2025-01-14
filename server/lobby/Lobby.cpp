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

#include "Lobby.hpp"

namespace rtype {

  Lobby::Lobby(zef::Engine& engine) : _engine(engine) {
  }

  void Lobby::RegisterLobbyCmd() {
    for (int i = 0; i < LOBBY_SIZE; i++) {
      room_t new_room  = {};
      new_room.name    = LOBBY + std::to_string(i);
      new_room.players = {};
      new_room.pwd     = DEFAULT_PWD;
      new_room.slot    = LOBBY_SIZE;
      new_room.owner   = DEFAULT_OWNER;
      new_room.running = false;

      // room_t new_room = {
      //     .name    = LOBBY + std::to_string(i),
      //     .players = {},
      //     .pwd     = DEFAULT_PWD,
      //     .slot    = LOBBY_SIZE,
      //     .owner   = DEFAULT_OWNER,
      //     .running = false,
      // };
      _lobby.push_back(new_room);
    }
    LobbyGetCmd();
    LobbySetCmd();
    LobbyActionCmd();
    lobbyDeleteCmd();
    lobbyUpdateCmd();
  }

  void Lobby::set_game_running(int room) {
    _lobby.at(room).running = true;
  }

  std::vector<room_t> Lobby::get_lobby() const {
    return _lobby;
  }

  Lobby::~Lobby() {
  }

}  // namespace rtype
