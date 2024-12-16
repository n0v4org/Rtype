/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Join
*/

#include <iostream>
#include <string>

#include "Commands/Join.hpp"
#include "Lobby.hpp"

static const char LOBBY_NOT_FOUND[]  = "404 Lobby not found";
static const char MAX_PLAYER[]       = "403 Maximum number of players reached";
static const char ALREADY_IN_LOBBY[] = "402 Already in lobby";
static const char SUCCEED[]          = "200 : lobby join";

Join::Join(json data) : ACommand(data) {
}

void Join::exec_cmd(std::string payload, asio::ip::tcp::socket &socket) {
  if (!parse_input(payload))
    return;
  int lobby_id = std::stoi(get_payload().at(0));
  if (LOBBY.size() < lobby_id) {
    set_resp(LOBBY_NOT_FOUND);
    return;
  }
  if (LOBBY.at(lobby_id).endpoints.size() > 5) {
    set_resp(MAX_PLAYER);
    return;
  }
  for (auto &i : LOBBY.at(lobby_id).endpoints) {
    if (i == socket.remote_endpoint()) {
      set_resp(ALREADY_IN_LOBBY);
      return;
    }
  }
  for (auto &i : LOBBY) {
    auto it = std::find(i.endpoints.begin(), i.endpoints.end(), socket.remote_endpoint());
    if (it != i.endpoints.end()) {
      i.endpoints.erase(it);
    }
  }
  LOBBY.at(lobby_id).endpoints.push_back(socket.remote_endpoint());
  set_resp(SUCCEED);
}

Join::~Join() {
}
