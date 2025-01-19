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
#include <map>
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
#include "GamerT.hpp"
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
    std::vector<std::pair<std::string, int>> _players_tcp;
    std::vector<std::pair<std::string, int>> _players_udp;
    std::vector<game_player_t> _players;
    zef::Engine _engine;

    void send_error(int id, const std::string &ec, int status);
    bool bad_args(input_t input, int nb_args);
    void register_tcp_game_cmd();
    void register_udp_game_cmd();
    void check_game_start(input_t input);
  };

}  // namespace rtype

#endif /* !GAME_HPP_ */
