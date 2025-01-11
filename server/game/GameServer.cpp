/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** game
*/

#include <vector>
#include <cmath>
#include <iostream>
#include <random>

#include "GameServer.hpp"

namespace rtype {

    GameServer::GameServer(int udp_port, int tcp_port) {
        _engine.initServer(udp_port, tcp_port);
        RegisterTcpCmd();
        RegisterUdpCmd();
        _engine.addSystem<>(ENGINE_NAME, zef::sys::handle_server);
    }

    void GameServer::run() {
        _engine.run();
    }

    bool GameServer::tcp_bad_args(input_t input, int nb_args, std::string ec) {
        int nb_cmd = std::count(input.tcp_payload.begin(), input.tcp_payload.end(), SP);

        if (nb_cmd == 0) {
            if (input.tcp_payload.empty() && nb_args == 0) {
                return false;
            }
             if (!input.tcp_payload.empty() && nb_args == 1)
                return false;
        }
        if (nb_cmd - 1 != nb_args) {
            _engine.ServerSendTcp(input.id, ec);
            return true;
        }
        return false;
    }

    bool GameServer::tcp_bad_room(input_t input, int room, std::string ec) {
        if (room < 0 || room > LOBBY_SIZE) {
            _engine.ServerSendTcp(input.id, TCP_ERRORS.at(LOBBY_NOT_FOUND));   
            return true;
        }
        return false;
    }

    void GameServer::RegisterTcpCmd() {

        // Command to retrieve info on all lobby
        _engine.registerCommandTcp(GET_ALL_LOBBY_CMD, [this ](zef::Engine& engine, input_t input) {
            std::string res = CMD_RES.at(GET_ALL_LOBBY_CMD).at(SUCCESS);
            
            if (tcp_bad_args(input, std::stoi(CMD_RES.at(GET_ALL_LOBBY_CMD).at(NB_ARGS)), TCP_ERRORS.at(INVALID_ARGS)))
                return;
            for (int i = 0; i < LOBBY_SIZE; i++) {
                res += ROOM + std::to_string(i) + SP;
                for (int j = 0; j < _lobby.at(i).size(); j++) {
                    int id = _lobby.at(i).at(j);
                    res += (_usernames.find(id) == _usernames.end()) ? PLAYER + std::to_string(j) + SP : _usernames.at(id);
                }
                res += ";";
            }
            _engine.ServerSendTcp(input.id, res);
        });

        // Command to retrieve info on a target room
        _engine.registerCommandTcp(GET_LOBBY_CMD, [this](zef::Engine& engine, input_t input) {
            std::string res = CMD_RES.at(GET_LOBBY_CMD).at(SUCCESS);

            if (tcp_bad_args(input, std::stoi(CMD_RES.at(GET_LOBBY_CMD).at(NB_ARGS)), TCP_ERRORS.at(INVALID_ARGS)))
                return;
            int room = std::stoi(input.tcp_payload);
            if (tcp_bad_room(input, room, TCP_ERRORS.at(LOBBY_NOT_FOUND)))
                return;
            res += std::to_string(room) + SP;
            for (int j = 0; j < _lobby.at(room).size(); j++) {
                int id = _lobby.at(room).at(j);
                res += (_usernames.find(id) == _usernames.end()) ? PLAYER + std::to_string(j) + SP : _usernames.at(id);
            }
            _engine.ServerSendTcp(input.id, res); 
        });

        // Command to set an username
        _engine.registerCommandTcp(SET_USERNAME_CMD, [this](zef::Engine& engine, input_t input) {
            std::string res = CMD_RES.at(SET_USERNAME_CMD).at(SUCCESS);

            if (tcp_bad_args(input, std::stoi(CMD_RES.at(SET_USERNAME_CMD).at(NB_ARGS)), TCP_ERRORS.at(INVALID_ARGS)))
                return;
            _usernames[input.id] = input.tcp_payload;
            res += _usernames[input.id];
            _engine.ServerSendTcp(input.id, res);
        });

        // Command to join a room
        _engine.registerCommandTcp(JOIN_ROOM_CMD, [this](zef::Engine& engine, input_t input) {
            std::string res = CMD_RES.at(JOIN_ROOM_CMD).at(SUCCESS);

            if (tcp_bad_args(input, std::stoi(CMD_RES.at(JOIN_ROOM_CMD).at(NB_ARGS)), TCP_ERRORS.at(INVALID_ARGS)))
                return;
            int room = std::stoi(input.tcp_payload);
            if (tcp_bad_room(input, room, TCP_ERRORS.at(LOBBY_NOT_FOUND)))
                return;
            if (_lobby.at(room).size() >= LOBBY_SIZE) { 
                _engine.ServerSendTcp(input.id, TCP_ERRORS.at(FULL_ROOM));   
                return;
            }
            for (auto id: _lobby.at(room)) {
                if (id == input.id) {
                    _engine.ServerSendTcp(input.id, TCP_ERRORS.at(ALREADY_IN_ROOM));
                    return;
                }
            }
            _lobby.at(room).push_back(input.id);
            res += std::to_string(room);
            _engine.ServerSendTcp(input.id, res);
        });

        // Command to quit a room
        _engine.registerCommandTcp(QUIT_ROOM_CMD, [this](zef::Engine& engine, input_t input) {
            std::string res = CMD_RES.at(QUIT_ROOM_CMD).at(SUCCESS);

            if (tcp_bad_args(input, std::stoi(CMD_RES.at(QUIT_ROOM_CMD).at(NB_ARGS)), TCP_ERRORS.at(INVALID_ARGS)))
                return;
            int room = std::stoi(input.tcp_payload);
            if (tcp_bad_room(input, room, TCP_ERRORS.at(LOBBY_NOT_FOUND)))
                return;
            std::vector<int>::iterator it = std::find(_lobby.at(room).begin(),_lobby.at(room).end(), input.id);
            if (it == _lobby.at(room).end()) {
                _engine.ServerSendTcp(input.id, TCP_ERRORS.at(NOT_IN_ROOM));
                return;
            }
            _lobby.at(room).erase(it);
            res += std::to_string(room);
            _engine.ServerSendTcp(input.id, res);
        });
    }

    void GameServer::RegisterUdpCmd() {

    }

    GameServer::~GameServer() {

    }

} // namespace rtype