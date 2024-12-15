/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Launch
*/

#include <iostream>
#include <string>

#include "Lobby.hpp"
#include "Commands/Launch.hpp"

static const char NOT_IN_LOBBY[] = " 401 Client is not in a lobby";
static const char SUCCESS[] = "200 game is launching";

Launch::Launch(json data)
: ACommand(data)
{
}

void Launch::exec_cmd(std::string payload, asio::ip::tcp::socket &socket) {
    bool status = false;

    if (!parse_input(payload))
        return;
    int lobby_id = std::stoi(get_payload().at(0));
    auto it = std::find(LOBBY[lobby_id].begin(), LOBBY[lobby_id].end(), socket.remote_endpoint());
    if (it == LOBBY[lobby_id].end()) {
        set_resp(NOT_IN_LOBBY);
        return;
    }
    //launch the game here;
    set_resp(SUCCESS);;
}

Launch::~Launch()
{
}

