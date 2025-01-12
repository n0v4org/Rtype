/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** delete
*/

#include <vector>
#include <cmath>
#include <sstream>
#include <iostream>
#include <random>
#include <string>

#include "Lobby.hpp"

namespace rtype {

  void Lobby::lobbyDeleteCmd() {
    // Command to delete a room
    _engine.registerCommandTcp(DELETE_ROOM_CMD, [this](zef::Engine& engine,
                                                       input_t input) {
      std::string res = CMD_RES.at(DELETE_ROOM_CMD).at(SUCCESS);
      if (bad_args(input, std::stoi(CMD_RES.at(DELETE_ROOM_CMD).at(NB_ARGS))) ||
          !is_number(input.tcp_payload, input.id))
        return;
      int room = std::stoi(input.tcp_payload);
      if (bad_room(input, room) || bad_perm(input, room))
        return;
      res += std::to_string(room);
      _lobby.erase(_lobby.begin() + room);
      _engine.ServerSendTcp(input.id, res);
    });
  }

}  // namespace rtype