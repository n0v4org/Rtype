/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Launch
*/

#include <iostream>
#include <string>
#include <random>

#include "Lobby.hpp"
#include "Commands/Launch.hpp"

static int MAX_PORT                     = 65535;
static int MIN_PORT                     = 1024;
static const char BAD_PORT[22]          = "port must be a number";
static const char PORT_OUT_OF_RANGE[36] = "port must be between 1024 and 65535";
static const char NOT_IN_LOBBY[]        = " 401 Client is not in a lobby";
static const char SUCCESS[]             = "200 game is launching at : ";

Launch::Launch(json data) : ACommand(data) {
}

int Launch::generateRandomPort() {
  constexpr int min_port = 1024;
  constexpr int max_port = 65535;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(min_port, max_port);

  return dis(gen);
}

void Launch::exec_cmd(std::string payload, asio::ip::tcp::socket &socket) {
  bool status = false;

  if (!parse_input(payload))
    return;
  int lobby_id = std::stoi(get_payload().at(0));
  auto it =
      std::find(LOBBY[lobby_id].endpoints.begin(),
                LOBBY[lobby_id].endpoints.end(), socket.remote_endpoint());
  if (it == LOBBY[lobby_id].endpoints.end()) {
    set_resp(NOT_IN_LOBBY);
    return;
  }
  LOBBY[lobby_id].launched = true;
  set_resp(SUCCESS + std::to_string(LOBBY.at(lobby_id).port));
}

Launch::~Launch() {
}
