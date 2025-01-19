/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** Lobby
*/

#ifndef LOBBY_HPP_
#define LOBBY_HPP_

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
  STATUS  = 2,
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
  NOT_ADMIN                 = 10,
  NOT_READY                 = 11,
  NOT_A_NUMBER              = 12,
  GAME_ALREADY_RUNNING      = 13,
  TOO_FEW_PLAYERS           = 14,
};

static const char GET_ALL_LOBBY_CMD[]    = "GET_ALL_LOBBY";
static const char SET_USERNAME_CMD[]     = "SET_USERNAME";
static const char JOIN_ROOM_CMD[]        = "JOIN";
static const char GET_LOBBY_CMD[]        = "GET_LOBBY";
static const char QUIT_ROOM_CMD[]        = "QUIT";
static const char SET_ROOM_CMD[]         = "SET_NEW_LOBBY";
static const char DELETE_ROOM_CMD[]      = "DELETE_LOBBY";
static const char LAUNCH_GAME_CMD[]      = "LAUNCH_GAME";
static const char SET_PLAYER_READY_CMD[] = "SET_PLAYER_READY";
static const char UPDATE_ROOM_CMD[]      = "UPDATE_LOBBY";
static const char UPDATE_PERM_CMD[]      = "UPDATE_PERM";
static const char KICK_PLAYER_CMD[]      = "KICK_PLAYER";
static const char SEND_MSG_CMD[]         = "SEND_MSG";
static const char GET_LOBBY_ID_CMD[] = "GET_LOBBY_ID";
static const char GET_PLAYER_DATA_CMD[] = "GET_PLAYER_DATA";

static const char CHARSET[] =
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
static const char SP            = ' ';
static const char PLAYER[]      = "player";
static const char ROOM[]        = "room";
static const char LOBBY[]       = "lobby";
static const char DEFAULT_PWD[] = "magicarpe";

static const int DEFAULT_OWNER      = -1;
static const uint8_t LOBBY_SIZE     = 5;
static const uint16_t NB_TCP_CMD    = 3;
static const uint16_t NB_TCP_ERRORS = 15;

static const std::array<std::pair<int, std::string>, NB_TCP_ERRORS> TCP_ERRORS =
    {{{400, "invalid args"},
      {401, "maximum number of players reached"},
      {402, "room not found"},
      {403, "player already in lobby"},
      {404, "player is not in this lobby"},
      {405, "invalid password"},
      {406, "nb slot should be > 0 && < 5"},
      {407, "lobby name already exist please provide an other one"},
      {408, "only the owner has the right"},
      {409, "default lobby you do not have the right baka"},
      {410, "only admin can launch the game"},
      {411, "some players are not ready"},
      {412, "some parameters must be numbers"},
      {413, "game already running"},
      {414, "too few players to start a game"}}};

static const std::map<std::string, std::array<std::string, NB_TCP_CMD>>
    CMD_RES = {
        {GET_ALL_LOBBY_CMD, {"successfully get data on all lobby", "0", "200"}},
        {SET_USERNAME_CMD, {"Username set successfully to ", "1", "201"}},
        {JOIN_ROOM_CMD, {"successfully join room ", "2", "202"}},
        {GET_LOBBY_CMD, {"succesfully get data on lobby ", "1", "203"}},
        {QUIT_ROOM_CMD, {"successfully quit room ", "0", "204"}},
        {SET_ROOM_CMD, {"successfully created lobby ", "3", "205"}},
        {DELETE_ROOM_CMD, {"successfully deleted lobby ", "0", "206"}},
        {LAUNCH_GAME_CMD, {"launching game in lobby ", "0", "207"}},
        {SET_PLAYER_READY_CMD, {"player is ready ", "0", "208"}},
        {UPDATE_ROOM_CMD, {"successfully updated lobby ", "3", "209"}},
        {UPDATE_PERM_CMD, {"successfully updated perm of ", "2", "210"}},
        {KICK_PLAYER_CMD, {"kick player ", "1", "211"}},
        {SEND_MSG_CMD, {"send message in lobby ", "1", "212"}},
        {GET_LOBBY_ID_CMD, {"successfully get lobby id ", "0", "213"}},
        {GET_PLAYER_DATA_CMD, {"successfully get data of player", "0", "214"}}};

struct player_t {
  int id;
  bool is_admin;
  bool is_ready;
};

struct room_t {
  std::string name;
  std::vector<player_t> players;
  std::string pwd;
  int slot;
  int owner;
  bool running;
};

using json = nlohmann::json;

namespace rtype {

  class Lobby {
  public:
    explicit Lobby(zef::Engine &_engine);
    void RegisterLobbyCmd();
    bool bad_args(input_t input, int nb_args);
    bool bad_room(input_t input, int room);
    void send_error(int id, const std::string &ec, int status);
    bool is_number(const std::string &s, int id);
    std::string generateFixedLengthString();
    std::vector<room_t> get_lobby() const;
    void set_game_running(int room);
    json get_data_single_room(room_t room, int room_id);
    int get_lobby_id(input_t input);
    ~Lobby();

  protected:
  private:
    void LobbyGetCmd();
    void LobbySetCmd();
    void LobbyActionCmd();
    void lobbyDeleteCmd();
    void lobbyUpdateCmd();
    bool bad_perm(input_t input, int nb_args);
    std::vector<std::string> parse_input(std::string input);
    int get_player_lobby(int player_id);

    zef::Engine &_engine;
    std::map<int, std::string> _usernames;
    std::vector<room_t> _lobby;
  };

}  // namespace rtype

#endif /* !LOBBY_HPP_ */
