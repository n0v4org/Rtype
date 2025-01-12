/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** game
*/

#include <vector>
#include <cmath>
#include <sstream>
#include <iostream>
#include <random>
#include <string>

#include "Lobby.hpp"

namespace rtype {

  Lobby::Lobby(zef::Engine& engine) : _engine(engine) {
  }

  // ----------------------------------------------------------------
  // ERROR HANDLING
  // ----------------------------------------------------------------

  bool Lobby::bad_args(input_t input, int nb_args) {
    int nb_cmd =
        std::count(input.tcp_payload.begin(), input.tcp_payload.end(), SP);

    if (nb_cmd == 0) {
      if (input.tcp_payload.empty() && nb_args == 0) {
        return false;
      }
      if (!input.tcp_payload.empty() && nb_args == 1)
        return false;
    }
    if (nb_cmd + 1 != nb_args) {
      _engine.ServerSendTcp(input.id, TCP_ERRORS.at(INVALID_ARGS));
      return true;
    }
    return false;
  }

  bool Lobby::bad_room(input_t input, int room) {
    if (room < 0 || room >= _lobby.size()) {
      _engine.ServerSendTcp(input.id, TCP_ERRORS.at(LOBBY_NOT_FOUND));
      return true;
    }
    return false;
  }

  bool Lobby::bad_perm(input_t input, int room) {
    if (_lobby.at(room).owner == DEFAULT_OWNER) {
      _engine.ServerSendTcp(input.id, TCP_ERRORS.at(NO_PERMS));
      return true;
    }
    std::vector<player_t>::iterator it = std::find_if(
        _lobby.at(room).players.begin(), _lobby.at(room).players.end(),
        [input](const player_t& player) {
          return input.id == player.id && player.is_admin;
        });
    if (it == _lobby.at(room).players.end() &&
        _lobby.at(room).owner != input.id) {
      _engine.ServerSendTcp(input.id, TCP_ERRORS.at(NOT_OWNER));
      return true;
    }
    return false;
  }

  bool Lobby::is_number(const std::string& s, int id) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    if (s.empty() || it != s.end()) {
      _engine.ServerSendTcp(id, TCP_ERRORS.at(NOT_A_NUMBER));
      return false;
    }
    return true;
    ;
  }

  // ----------------------------------------------------------------
  // PARSER
  // ----------------------------------------------------------------

  std::vector<std::string> Lobby::parse_input(std::string input) {
    std::stringstream ss(input.c_str());
    std::string line;
    std::vector<std::string> cmds;

    while (std::getline(ss, line, SP)) {
      cmds.push_back(line);
    }
    return cmds;
  }

  // ----------------------------------------------------------------
  // GET
  // ----------------------------------------------------------------

  void Lobby::LobbyGetCmd() {
    // Command to retrieve info on all lobby
    _engine.registerCommandTcp(GET_ALL_LOBBY_CMD, [this](zef::Engine& engine,
                                                         input_t input) {
      std::string res = CMD_RES.at(GET_ALL_LOBBY_CMD).at(SUCCESS);

      if (bad_args(input, std::stoi(CMD_RES.at(GET_ALL_LOBBY_CMD).at(NB_ARGS))))
        return;
      for (int i = 0; i < _lobby.size(); i++) {
        res += _lobby.at(i).name + SP + std::to_string(_lobby.at(i).slot) + SP;
        for (int j = 0; j < _lobby.at(i).players.size(); j++) {
          int id = _lobby.at(i).players.at(j).id;
          res += (_usernames.find(id) == _usernames.end())
                     ? PLAYER + std::to_string(j) + SP
                     : _usernames.at(id);
        }
        res += ";";
      }
      _engine.ServerSendTcp(input.id, res);
    });

    // Command to retrieve info on a target room
    _engine.registerCommandTcp(GET_LOBBY_CMD, [this](zef::Engine& engine,
                                                     input_t input) {
      std::string res = CMD_RES.at(GET_LOBBY_CMD).at(SUCCESS);

      if (bad_args(input, std::stoi(CMD_RES.at(GET_LOBBY_CMD).at(NB_ARGS))) ||
          !is_number(input.tcp_payload, input.id))
        return;
      int room = std::stoi(input.tcp_payload);
      if (bad_room(input, room))
        return;
      res +=
          _lobby.at(room).name + SP + std::to_string(_lobby.at(room).slot) + SP;
      for (int j = 0; j < _lobby.at(room).players.size(); j++) {
        int id = _lobby.at(room).players.at(j).id;
        res += (_usernames.find(id) == _usernames.end())
                   ? PLAYER + std::to_string(j) + SP
                   : _usernames.at(id) + SP;
      }
      _engine.ServerSendTcp(input.id, res);
    });
  }

  // ----------------------------------------------------------------
  // SET
  // ----------------------------------------------------------------

  void Lobby::LobbySetCmd() {
    // Command to set an username
    _engine.registerCommandTcp(SET_USERNAME_CMD, [this](zef::Engine& engine,
                                                        input_t input) {
      std::string res = CMD_RES.at(SET_USERNAME_CMD).at(SUCCESS);

      if (bad_args(input, std::stoi(CMD_RES.at(SET_USERNAME_CMD).at(NB_ARGS))))
        return;
      _usernames[input.id] = input.tcp_payload;
      res += _usernames[input.id];
      _engine.ServerSendTcp(input.id, res);
    });

    // Command to set a new room
    _engine.registerCommandTcp(SET_ROOM_CMD, [this](zef::Engine& engine,
                                                    input_t input) {
      std::string res = CMD_RES.at(SET_ROOM_CMD).at(SUCCESS);

      if (bad_args(input, std::stoi(CMD_RES.at(SET_ROOM_CMD).at(NB_ARGS))))
        return;
      std::vector<std::string> parsed_input = parse_input(input.tcp_payload);
      std::string name                      = parsed_input.at(0);
      if (!is_number(parsed_input.at(1), input.id))
        return;
      int slot        = std::stoi(parsed_input.at(1));
      std::string pwd = parsed_input.at(2);
      if (slot < 0 || slot > LOBBY_SIZE) {
        _engine.ServerSendTcp(input.id, TCP_ERRORS.at(INVALID_SLOT));
        return;
      }
      std::vector<room_t>::iterator it = std::find_if(
          _lobby.begin(), _lobby.end(),
          [&name](const room_t& room) { return room.name == name; });
      if (it != _lobby.end()) {
        _engine.ServerSendTcp(input.id,
                              TCP_ERRORS.at(LOBBY_NAME_ALREADY_EXISTS));
        return;
      }

      room_t new_room = {
          .name    = name,
          .players = {},
          .pwd     = pwd,
          .slot    = slot,
          .owner   = input.id,
      };
      _lobby.push_back(new_room);
      res += name;
      _engine.ServerSendTcp(input.id, res);
    });
  }

  // ----------------------------------------------------------------
  // ACTION
  // ----------------------------------------------------------------

  void Lobby::LobbyActionCmd() {
    // Command to join a room
    _engine.registerCommandTcp(JOIN_ROOM_CMD, [this](zef::Engine& engine,
                                                     input_t input) {
      std::string res = CMD_RES.at(JOIN_ROOM_CMD).at(SUCCESS);

      if (bad_args(input, std::stoi(CMD_RES.at(JOIN_ROOM_CMD).at(NB_ARGS))))
        return;

      std::vector<std::string> parsed_input = parse_input(input.tcp_payload);
      if (!is_number(parsed_input.at(0), input.id))
        return;
      int room        = std::stoi(parsed_input.at(0));
      std::string pwd = parsed_input.at(1);

      if (bad_room(input, room))
        return;
      if (_lobby.at(room).pwd != pwd) {
        _engine.ServerSendTcp(input.id, TCP_ERRORS.at(INVALID_PWD));
        return;
      }
      if (_lobby.at(room).players.size() >= LOBBY_SIZE) {
        _engine.ServerSendTcp(input.id, TCP_ERRORS.at(FULL_ROOM));
        return;
      }
      for (auto player : _lobby.at(room).players) {
        if (player.id == input.id) {
          _engine.ServerSendTcp(input.id, TCP_ERRORS.at(ALREADY_IN_ROOM));
          return;
        }
      }

      player_t new_player = {
          .id       = input.id,
          .is_admin = (_lobby.at(room).owner == input.id) ? true : false,
          .is_ready = false,
      };

      _lobby.at(room).players.push_back(new_player);
      res += std::to_string(room);
      _engine.ServerSendTcp(input.id, res);
    });

    // Command to quit a room
    _engine.registerCommandTcp(QUIT_ROOM_CMD, [this](zef::Engine& engine,
                                                     input_t input) {
      std::string res = CMD_RES.at(QUIT_ROOM_CMD).at(SUCCESS);

      if (bad_args(input, std::stoi(CMD_RES.at(QUIT_ROOM_CMD).at(NB_ARGS))) ||
          !is_number(input.tcp_payload, input.id))
        return;
      int room = std::stoi(input.tcp_payload);
      if (bad_room(input, room))
        return;
      std::vector<player_t>::iterator it = std::find_if(
          _lobby.at(room).players.begin(), _lobby.at(room).players.end(),
          [input](const player_t& player) { return input.id == player.id; });
      if (it == _lobby.at(room).players.end()) {
        _engine.ServerSendTcp(input.id, TCP_ERRORS.at(NOT_IN_ROOM));
        return;
      }
      _lobby.at(room).players.erase(it);
      res += std::to_string(room);
      _engine.ServerSendTcp(input.id, res);
    });

    // Command to laucnh a Game
    _engine.registerCommandTcp(LAUNCH_GAME_CMD, [this](zef::Engine& engine,
                                                       input_t input) {
      std::string res = CMD_RES.at(LAUNCH_GAME_CMD).at(SUCCESS);

      if (bad_args(input, std::stoi(CMD_RES.at(LAUNCH_GAME_CMD).at(NB_ARGS))) ||
          !is_number(input.tcp_payload, input.id))
        return;
      int room = std::stoi(input.tcp_payload);
      if (bad_room(input, room))
        return;
      std::vector<player_t>::iterator it = std::find_if(
          _lobby.at(room).players.begin(), _lobby.at(room).players.end(),
          [input](const player_t& player) { return player.id == input.id; });
      if (it == _lobby.at(room).players.end()) {
        _engine.ServerSendTcp(input.id, TCP_ERRORS.at(NOT_IN_ROOM));
        return;
      }
      if (!(*it).is_admin) {
        _engine.ServerSendTcp(input.id, TCP_ERRORS.at(NOT_ADMIN));
        return;
      }
      it = std::find_if(
          _lobby.at(room).players.begin(), _lobby.at(room).players.end(),
          [](const player_t& player) { return !player.is_ready; });
      if (it != _lobby.at(room).players.end()) {
        _engine.ServerSendTcp(input.id, TCP_ERRORS.at(NOT_READY));
        return;
      }
      // add logic to launch a game in intern
      res += _lobby.at(room).name;
      for (auto player : _lobby.at(room).players) {
        _engine.ServerSendTcp(player.id, res);
      }
    });
  }

  // ----------------------------------------------------------------
  // DEL
  // ----------------------------------------------------------------

  void Lobby::lobbyDeleteCmd() {
    // Command to delete a room
    _engine.registerCommandTcp(DELETE_ROOM_CMD, [this](zef::Engine& engine,
                                                       input_t input) {
      std::string res = CMD_RES.at(DELETE_ROOM_CMD).at(SUCCESS);
      if (bad_args(input, std::stoi(CMD_RES.at(DELETE_ROOM_CMD).at(NB_ARGS))) ||
          !is_number(input.tcp_payload, input.id))
        return;
      int room = std::stoi(input.tcp_payload);
      if (bad_room(input, room) || bad_perm(input, room))
        return;
      res += std::to_string(room);
      _lobby.erase(_lobby.begin() + room);
      _engine.ServerSendTcp(input.id, res);
    });
  }

  // ----------------------------------------------------------------
  // UPDATE
  // ----------------------------------------------------------------

  void Lobby::lobbyUpdateCmd() {
    // update ready status of a player
    _engine.registerCommandTcp(SET_PLAYER_READY_CMD, [this](zef::Engine& engine,
                                                            input_t input) {
      std::string res = CMD_RES.at(SET_PLAYER_READY_CMD).at(SUCCESS);
      if (bad_args(input, std::stoi(CMD_RES.at(DELETE_ROOM_CMD).at(NB_ARGS))) ||
          !is_number(input.tcp_payload, input.id))
        return;
      int room = std::stoi(input.tcp_payload);
      if (bad_room(input, room))
        return;
      std::vector<player_t>::iterator it = std::find_if(
          _lobby.at(room).players.begin(), _lobby.at(room).players.end(),
          [input](const player_t& player) { return player.id == input.id; });
      if (it == _lobby.at(room).players.end()) {
        _engine.ServerSendTcp(input.id, TCP_ERRORS.at(NOT_IN_ROOM));
        return;
      }
      (*it).is_ready = true;
      res += std::to_string((*it).id);
      _engine.ServerSendTcp(input.id, res);
    });

    // Command to update a room
    _engine.registerCommandTcp(UPDATE_ROOM_CMD, [this](zef::Engine& engine,
                                                       input_t input) {
      std::string res = CMD_RES.at(UPDATE_ROOM_CMD).at(SUCCESS);
      if (bad_args(input, std::stoi(CMD_RES.at(UPDATE_ROOM_CMD).at(NB_ARGS))))
        return;
      std::vector<std::string> parsed_input = parse_input(input.tcp_payload);
      if (!is_number(parsed_input.at(0), input.id) ||
          !is_number(parsed_input.at(2), input.id))
        return;
      int room               = std::stoi(parsed_input.at(0));
      std::string lobby_name = parsed_input.at(1);
      int slot               = std::stoi(parsed_input.at(2));
      std::string password   = parsed_input.at(3);
      if (bad_room(input, room) || bad_perm(input, room))
        return;
      if (slot < 0 || slot > LOBBY_SIZE) {
        _engine.ServerSendTcp(input.id, TCP_ERRORS.at(INVALID_SLOT));
        return;
      }
      std::vector<room_t>::iterator it = std::find_if(
          _lobby.begin(), _lobby.end(), [&lobby_name](const room_t& room) {
            return room.name == lobby_name;
          });
      if (it != _lobby.end()) {
        _engine.ServerSendTcp(input.id,
                              TCP_ERRORS.at(LOBBY_NAME_ALREADY_EXISTS));
        return;
      }
      _lobby.at(room).name = lobby_name;
      _lobby.at(room).slot = slot;
      _lobby.at(room).pwd  = password;
      res += std::to_string(room);
      _engine.ServerSendTcp(input.id, res);
    });
  }

  void Lobby::RegisterLobbyCmd() {
    for (int i = 0; i < LOBBY_SIZE; i++) {
      room_t new_room = {
          .name    = LOBBY + std::to_string(i),
          .players = {},
          .pwd     = DEFAULT_PWD,
          .slot    = LOBBY_SIZE,
          .owner   = DEFAULT_OWNER,
      };
      _lobby.push_back(new_room);
    }
    LobbyGetCmd();
    LobbySetCmd();
    LobbyActionCmd();
    lobbyDeleteCmd();
    lobbyUpdateCmd();
  }

  Lobby::~Lobby() {
  }

}  // namespace rtype
