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

#include "macro.hpp"
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
      int room = get_lobby_id(input);
      if (room == KO)
        return;
      if (bad_room(input, room) || bad_perm(input, room))
        return;
      res += std::to_string(room);
      _lobby.erase(_lobby.begin() + room);
      json data;
      data["status"]      = std::stoi(CMD_RES.at(DELETE_ROOM_CMD).at(STATUS));
      data["description"] = res;
      data["room_id"]     = room;
      _engine.ServerSendToAllTcp(data.dump());
    });
  }

}  // namespace rtype