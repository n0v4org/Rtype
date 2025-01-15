/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <thread>
#include <vector>
#include <string>
#include <utility>
#include <array>

#include <nlohmann/json.hpp>

#include "Engine.hpp"
#include "Scenes.hpp"
#include "systems.hpp"

#include "CommonCommands.hpp"

#include "modules/display/systems.hpp"
#include "modules/movement/systems.hpp"
#include "modules/network/systems.hpp"

#include "modules/IModule.hpp"

enum {
  GAME_SUCCESS = 0,
  GAME_NB_ARGS = 1,
  GAME_STATUS  = 2,
};

enum {
  GAME_INVALID_ARGS              = 0,
  WRONG_PWD                 = 1,
};

static const char LOGIN_CMD[] = "LOGIN";
static const char START_GAME_CMD[] = "START";

static const uint16_t GAME_NB_TCP_CMD    = 3;
static const uint16_t GAME_NB_TCP_ERRORS = 2;

static const std::array<std::pair<int, std::string>, GAME_NB_TCP_ERRORS> GAME_TCP_ERRORS =
    {{{420, "invalid args"},
      {421, "invalid login code"}}};

static const std::map<std::string, std::array<std::string, GAME_NB_TCP_CMD>>
    CMD_TCP_RES = {
        {LOGIN_CMD, {"successfully logged in", "1", "220"}},
        {START_GAME_CMD, {"game is starting", "0", "221"}}
        };

using json = nlohmann::json;

namespace rtype {

  class Game {
  public:
    Game();
    void RegisterGameCmd();
    void launch_game(std::vector<std::string> player_uuid, int tcp_port,
                     int udp_port);
    void init_game(std::vector<std::string> player_uuid, int tcp_port,
                   int udp_port);
    ~Game();

  protected:
  private:
    std::vector<std::thread> _games;
    std::vector<std::string> _player_uuid;
    std::vector<int> _players_tcp;
    std::vector<int> _players_udp;
    zef::Engine _engine;

    void send_error(int id, const std::string &ec, int status);
    bool bad_args(input_t input, int nb_args);
    void register_tcp_game_cmd();
  };

}  // namespace rtype

#endif /* !GAME_HPP_ */
