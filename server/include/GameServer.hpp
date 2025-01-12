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
#include <memory>
#include <utility>

#include "Engine.hpp"
#include "Scenes.hpp"
#include "systems.hpp"

#include "CommonCommands.hpp"

#include "modules/display/systems.hpp"
#include "modules/movement/systems.hpp"
#include "modules/network/systems.hpp"

#include "modules/IModule.hpp"

#include "Lobby.hpp"

static const char ENGINE_NAME[] = "zefir";

namespace rtype {

  class GameServer {
  public:
    GameServer(int udp_port, int tcp_port);
    void run();
    ~GameServer();

  protected:
  private:
    zef::Engine _engine;
    std::unique_ptr<Lobby> _lobby;
  };

}  // namespace rtype
#endif /* !GAMESERVER_HPP_ */
