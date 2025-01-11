/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** GameServer
*/

#ifndef GAMESERVER_HPP_
#define GAMESERVER_HPP_

#include <vector>
#include <array>
#include <string>
#include <cmath>
#include <iostream>
#include <map>
#include <random>
#include <utility>

#include "Engine.hpp"
#include "Scenes.hpp"
#include "systems.hpp"

#include "CommonCommands.hpp"

#include "modules/display/systems.hpp"
#include "modules/movement/systems.hpp"
#include "modules/network/systems.hpp"

#include "modules/IModule.hpp"

enum {
  SUCCESS = 0,
  NB_ARGS = 1,
};

enum {
  INVALID_ARGS              = 0,
  FULL_ROOM                 = 1,
  LOBBY_NOT_FOUND           = 2,
  ALREADY_IN_ROOM           = 3,
  NOT_IN_ROOM               = 4,
  INVALID_PWD               = 5,
  INVALID_SLOT              = 6,
  LOBBY_NAME_ALREADY_EXISTS = 7,
  NOT_OWNER                 = 8,
  NO_PERMS                  = 9,
};

static const char GET_ALL_LOBBY_CMD[] = "GET_ALL_LOBBY";
static const char SET_USERNAME_CMD[]  = "SET_USERNAME";
static const char JOIN_ROOM_CMD[]     = "JOIN";
static const char GET_LOBBY_CMD[]     = "GET_LOBBY";
static const char QUIT_ROOM_CMD[]     = "QUIT";
static const char SET_ROOM_CMD[]      = "SET_NEW_LOBBY";
static const char DELETE_ROOM_CMD[]   = "DELETE_LOBBY";

static const char SP            = ' ';
static const char PLAYER[]      = "player";
static const char ENGINE_NAME[] = "zefir";
static const char ROOM[]        = "room";
static const char LOBBY[]       = "lobby";
static const char DEFAULT_PWD[] = "magicarpe";

static const int DEFAULT_OWNER      = -1;
static const uint8_t LOBBY_SIZE     = 5;
static const uint16_t NB_TCP_CMD    = 2;
static const uint16_t NB_TCP_ERRORS = 10;

static const std::array<std::string, NB_TCP_ERRORS> TCP_ERRORS = {
    "400 invalid args",
    "401 maximum number of players reached",
    "404 room not found",
    "402 player already in lobby",
    "404 player is not in a lobby",
    "403 invalid password",
    "402 nb slot should be > 0 && < 5",
    "401 lobby name already exist please provide an other one",
    "403 only the owner can delete this lobby",
    "403 default lobby you do not have the right baka"};

static const std::map<std::string, std::array<std::string, NB_TCP_CMD>>
    CMD_RES = {
        {GET_ALL_LOBBY_CMD, {"200 ", "0"}},
        {SET_USERNAME_CMD, {"200 Username set successfully to ", "1"}},
        {JOIN_ROOM_CMD, {"200 successfully join room ", "2"}},
        {GET_LOBBY_CMD, {"200  ", "1"}},
        {QUIT_ROOM_CMD, {"200 successfully quit room ", "1"}},
        {SET_ROOM_CMD, {"successfully created lobby ", "3"}},
        {DELETE_ROOM_CMD, {"200 successfully deleted lobby ", "1"}},
};

struct room_t {
  std::string name;
  std::vector<int> players;
  std::string pwd;
  int slot;
  int owner;
};

namespace rtype {

  class GameServer {
  public:
    GameServer(int udp_port, int tcp_port);
    void run();
    ~GameServer();

  protected:
  private:
    void RegisterUdpCmd();
    void RegisterTcpCmd();
    void LobbyGetCmd();
    void LobbySetCmd();
    void LobbyActionCmd();
    void lobbyDeleteCmd();
    bool tcp_bad_room(input_t input, int room, std::string ec);
    bool tcp_bad_args(input_t input, int nb_args, std::string ec);
    std::vector<std::string> parse_input(std::string input);

    zef::Engine _engine;
    std::map<int, std::string> _usernames;
    std::vector<room_t> _lobby;
  };

}  // namespace rtype
#endif /* !GAMESERVER_HPP_ */
