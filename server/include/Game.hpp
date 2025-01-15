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

static const char LOGIN_CMD[] = "LOGIN";

static const uint16_t GAME_NB_TCP_CMD    = 3;

static const std::map<std::string, std::array<std::string, GAME_NB_TCP_CMD>>
    CMD_TCP_RES = {
        {LOGIN_CMD, {"send message in lobby ", "1", "220"}}};

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
    void send_error(int id, const std::string &ec, int status);
    bool bad_args(input_t input, int nb_args);
    void register_tcp_game_cmd();
    zef::Engine _engine;
  };

}  // namespace rtype

#endif /* !GAME_HPP_ */
