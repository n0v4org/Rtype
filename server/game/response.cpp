/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** response
*/

#include <string>

#include "Game.hpp"

namespace rtype {

  void Game::send_error(int id, const std::string &ec, int status) {
    json res = {
        {"description", ec},
        {"status", status},
    };
    std::string json_str = res.dump();
    _engine.ServerSendTcp(id, json_str);
  }
} // namespace rtype