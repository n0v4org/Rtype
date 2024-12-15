/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** GetAllLobby
*/

#include <iostream>
#include <string>

#include "Lobby.hpp"
#include "Commands/GetAllLobby.hpp"

GetAllLobby::GetAllLobby(json data) : ACommand(data) {
}

void GetAllLobby::exec_cmd(std::string payload,
                           asio::ip::tcp::socket &socket_) {
  std::string resp = "200 ";

  if (!parse_input(payload))
    return;
  resp += "0";
  for (int i = 1; i < LOBBY.size(); i++) {
    resp += " " + std::to_string(i);
  }
  set_resp(resp);
}

GetAllLobby::~GetAllLobby() {
}
