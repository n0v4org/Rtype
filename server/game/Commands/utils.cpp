/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** utils
*/

#include "Game.hpp"
#include "tcp_cmds.hpp"

namespace rtype {
    void Game::check_game_start(input_t input) {
      if (_players_tcp.size() == _player_uuid.size() && _players_udp.size() == _player_uuid.size()) {
        for (auto &uuid: _player_uuid) {
            game_player_t new_player = {};
            auto tcp_id = std::find_if(_players_tcp.begin(), _players_tcp.end(), [uuid](const std::pair<std::string, int> &player) {
                return player.first == uuid;
            });
            auto udp_id = std::find_if(_players_udp.begin(), _players_udp.end(), [uuid](const std::pair<std::string, int> &player) {
                return player.first == uuid;
            });
            if (tcp_id == _players_tcp.end() || udp_id == _players_udp.end()) {
                std::cerr << "error that i thought won't happen si fuck you" << std::endl;
            }
            new_player.tcp_id = tcp_id->second;
            new_player.udp_id = udp_id->second;
            _players.push_back(new_player);
        }
        for (int j = 0; j < _players.size(); j++) {
            json start_json;
            start_json["status"] = std::stoi(CMD_TCP_RES.at(START_GAME_CMD).at(GAME_STATUS));
            start_json["description"] = CMD_TCP_RES.at(START_GAME_CMD).at(GAME_SUCCESS);
            start_json["players"] = json::array();
            for (int i = 0; i < _players.size(); i++) {
                if (i == j)
                    continue;
                start_json["players"].push_back({"id", i});
            }
            _engine.ServerSendTcp(_players.at(j).tcp_id, start_json.dump());
        }
      }
    }
}