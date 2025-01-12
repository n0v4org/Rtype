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
      room_t new_room = {
          .name    = LOBBY + std::to_string(i),
          .players = {},
          .pwd     = DEFAULT_PWD,
          .slot    = LOBBY_SIZE,
          .owner   = DEFAULT_OWNER,
          .running = false,
      };
      _lobby.push_back(new_room);
    }
    LobbyGetCmd();
    LobbySetCmd();
    LobbyActionCmd();
    lobbyDeleteCmd();
    lobbyUpdateCmd();
  }

  Lobby::~Lobby() {
  }

}  // namespace rtype
