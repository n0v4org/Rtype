/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** GetLobby
*/

#include <iostream>
#include <string>

#include "Lobby.hpp"
#include "Commands/GetLobby.hpp"

static const char LOBBY_NOT_FOUND[] = "404 Lobby not found";

GetLobby::GetLobby(json data) : ACommand(data) {
}

void GetLobby::exec_cmd(std::string payload, asio::ip::tcp::socket &socket_) {
  std::string resp = "200 ";

  if (!parse_input(payload))
    return;
  int lobby_id = std::stoi(get_payload().at(0));
  if (LOBBY.size() < lobby_id) {
    set_resp(LOBBY_NOT_FOUND);
    return;
  }
  for (auto &i : LOBBY.at(lobby_id).endpoints) {
    resp += i.address().to_string() + ":" + std::to_string(i.port()) + " ";
  }
  set_resp(resp);
}

GetLobby::~GetLobby() {
}
