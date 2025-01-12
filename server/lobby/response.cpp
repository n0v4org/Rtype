/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** response
*/

#include <vector>
#include <cmath>
#include <sstream>
#include <iostream>
#include <random>
#include <string>

#include <nlohmann/json.hpp>
#include "Lobby.hpp"

namespace rtype {

    void Lobby::send_error(int id, const std::string &ec, int status) {
        json res = {
            {"description", ec},
            {"status", status},
        };
        std::string json_str = res.dump();
        _engine.ServerSendTcp(id, json_str);
    }

    json Lobby::get_data_single_room(room_t room, int room_id) {
        json res = {
            {"rooms_id", room_id},
            {"room_name", room.name},
            {"slot", room.slot},
            {"running", room.running},
        };
        res["players"] = json::array();
        for (auto &player: room.players) {
            json json_player =  {
                {"id", player.id},
                {"is_admin", player.is_admin},
                {"is_ready", player.is_ready},
                {"username", _usernames.at(player.id)},
            };
            res["players"].push_back(json_player);
        }
        return res;
    }

}  // namespace rtype