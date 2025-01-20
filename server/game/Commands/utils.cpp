/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** utils
*/

#include <utility>
#include <string>
#include <iostream>
#include "Game.hpp"
#include "tcp_cmds.hpp"
#include "PlanePatron.hpp"
#include "EnemyRobotPatron.hpp"
#include "EnemyPlanePatron.hpp"
#include "BossOnePatron.hpp"

namespace rtype {
  void Game::check_game_start(input_t input) {
    if (_players_tcp.size() == _player_uuid.size() &&
        _players_udp.size() == _player_uuid.size()) {
      for (auto &uuid : _player_uuid) {
        game_player_t new_player = {};
        auto tcp_id =
            std::find_if(_players_tcp.begin(), _players_tcp.end(),
                         [uuid](const std::pair<std::string, int> &player) {
                           return player.first == uuid;
                         });
        auto udp_id =
            std::find_if(_players_udp.begin(), _players_udp.end(),
                         [uuid](const std::pair<std::string, int> &player) {
                           return player.first == uuid;
                         });
        if (tcp_id == _players_tcp.end() || udp_id == _players_udp.end()) {
          std::cerr << "error that i thought won't happen si fuck you"
                    << std::endl;
        }
        new_player.tcp_id = tcp_id->second;
        new_player.udp_id = udp_id->second;
        _players.push_back(new_player);
      }
      for (int j = 0; j < _players.size(); j++) {
        
        json start_json;
        start_json["status"] =
            std::stoi(CMD_TCP_RES.at(START_GAME_CMD).at(GAME_STATUS));
        start_json["description"] =
            CMD_TCP_RES.at(START_GAME_CMD).at(GAME_SUCCESS);
        start_json["players"] = json::array();
        for (int i = 0; i < _players.size(); i++) {
          if (i == j)
            continue;
          start_json["players"].push_back({"id", i});
        }
        std::cout << "instanship " << j << std::endl;
        _engine.instanciatePatron<AllyPatron>(0.0f, 0.0f, static_cast<size_t>(j));
        _engine.ServerSendTcp(_players.at(j).tcp_id, start_json.dump());
      }
      sleep(1);
      for (int j = 0; j < _players.size(); j++) {
        rep_id = 345;
        _engine.instanciatePatron<sEnemyRobotPatron>(600.0f, 0.0f, rep_id);
        _engine.ServerSendUdp<spawn_robot_t>(_players.at(j).tcp_id, SPAWN_ROBOT, {rep_id, 600.0f, 0.0f} );
        rep_id++;
        _engine.instanciatePatron<sEnemyRobotPatron>(1200.0f, 0.0f, rep_id);
        _engine.ServerSendUdp<spawn_robot_t>(_players.at(j).tcp_id, SPAWN_ROBOT, {rep_id, 1200.0f, 0.0f} );
        rep_id++;
        _engine.instanciatePatron<sEnemyRobotPatron>(1800.0f, 0.0f, rep_id);
        _engine.ServerSendUdp<spawn_robot_t>(_players.at(j).tcp_id, SPAWN_ROBOT, {rep_id, 1800.0f, 0.0f} );
        rep_id++;

        _engine.instanciatePatron<EnemyPlanePatron>(700.0f, 100.0f, rep_id);
        _engine.ServerSendUdp<spawn_plane_t>(_players.at(j).tcp_id, SPAWN_PLANE, {rep_id, 700.0f, 100.0f} );
        rep_id++;
        _engine.instanciatePatron<EnemyPlanePatron>(2000.0f, 100.0f, rep_id);
        _engine.ServerSendUdp<spawn_plane_t>(_players.at(j).tcp_id, SPAWN_PLANE, {rep_id, 700.0f, 100.0f} );
        rep_id++;
        _engine.instanciatePatron<EnemyPlanePatron>(3000.0f, 100.0f, rep_id);
        _engine.ServerSendUdp<spawn_plane_t>(_players.at(j).tcp_id, SPAWN_PLANE, {rep_id, 700.0f, 100.0f} );
        rep_id++;


        _engine.instanciatePatron<BossOnePatron>(3000.0f, 0.0f, rep_id);
        _engine.ServerSendUdp<spawn_boss_t>(_players.at(j).tcp_id, SPAWN_BOSS, {rep_id, 3000.0f, 100.0f} );
        rep_id++;
        //_engine.instanciatePatron<EnemyPlanePatron>(800.0f, -400.0f, rep_id);
        //_engine.ServerSendUdp<spawn_plane_t>(_players.at(j).tcp_id, SPAWN_PLANE, {rep_id, 800.0f, -400.0f} );
        //rep_id++;
        //_engine.instanciatePatron<EnemyPlanePatron>(1500.0f, 0.0f, rep_id);
        //_engine.ServerSendUdp<spawn_plane_t>(_players.at(j).tcp_id, SPAWN_PLANE, {rep_id, 1500.0f, 0.0f} );
        //rep_id++;
        //_engine.instanciatePatron<EnemyPlanePatron>(2500.0f, 400.0f, rep_id);
        //_engine.ServerSendUdp<spawn_plane_t>(_players.at(j).tcp_id, SPAWN_PLANE, {rep_id, 2500.0f, 400.0f} );
        //rep_id++;
      }
        /*_engine.instanciatePatron<EnemyRobotPatron>(400.0f, 0.0f, rep_id);
        _engine.ServerSendUdp<spawn_robot_t>(_players.at(j).tcp_id, SPAWN_ROBOT, {rep_id, 400.0f, 0.0f});
        rep_id++;
        _engine.instanciatePatron<EnemyRobotPatron>(600.0f, 0.0f, rep_id);
        _engine.ServerSendUdp<spawn_robot_t>(_players.at(j).tcp_id, SPAWN_ROBOT, {rep_id, 600.0f, 0.0f});
        rep_id++;
        _engine.instanciatePatron<EnemyRobotPatron>(800.0f, 0.0f, rep_id);
        _engine.ServerSendUdp<spawn_robot_t>(_players.at(j).tcp_id, SPAWN_ROBOT, {rep_id, 800.0f, 0.0f});
        rep_id++;
        _engine.instanciatePatron<EnemyRobotPatron>(1000.0f, 0.0f, rep_id);
        _engine.ServerSendUdp<spawn_robot_t>(_players.at(j).tcp_id, SPAWN_ROBOT, {rep_id, 1000.0f, 0.0f});
        rep_id++;
        _engine.instanciatePatron<EnemyRobotPatron>(1200.0f, 0.0f, rep_id);
        _engine.ServerSendUdp<spawn_robot_t>(_players.at(j).tcp_id, SPAWN_ROBOT, {rep_id, 1200.0f, 0.0f});
        rep_id++;
        _engine.instanciatePatron<EnemyRobotPatron>(1400.0f, 0.0f, rep_id);
        _engine.ServerSendUdp<spawn_robot_t>(_players.at(j).tcp_id, SPAWN_ROBOT, {rep_id, 1400.0f, 0.0f});
        rep_id++;
        _engine.instanciatePatron<EnemyRobotPatron>(1600.0f, 0.0f, rep_id);
        _engine.ServerSendUdp<spawn_robot_t>(_players.at(j).tcp_id, SPAWN_ROBOT, {rep_id, 1600.0f, 0.0f});
        rep_id++;*/
      
    }
  }
}  // namespace rtype