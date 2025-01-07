/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** systems
*/

#ifndef ENGINE_MODULES_NETWORK_SYSTEMS_HPP_
#define ENGINE_MODULES_NETWORK_SYSTEMS_HPP_

#include "../../Engine.hpp"
#include "components.hpp"

struct hihi {
  int j;
};

namespace zef {
  namespace sys {
    void handle_server(zef::Engine& engine) {
      while (!engine._server->isQueueEmpty()) {
        input_t rcv = engine._server->popMessage();
        // std::cout << (int)rcv.cmd << std::endl;
        int cmdid = static_cast<int>(rcv.cmd);
        if (engine._cmd_map.find(cmdid) != engine._cmd_map.end())
          engine._cmd_map[cmdid](engine, rcv);
      }
    }
    void handle_client(zef::Engine& engine) {
      //while (!engine._client->isQueueEmpty()) {
      //  input_t rcv = engine._client->popMessage();
      //  // std::cout << (int)rcv.cmd << std::endl;
      //  int cmdid = static_cast<int>(rcv.cmd);
      //  if (engine._cmd_map.find(cmdid) != engine._cmd_map.end())
      //    engine._cmd_map[cmdid](engine, rcv);
     // }
    }
  }  // namespace sys

}  // namespace zef

#endif  // !ENGINE_MODULES_NETWORK_SYSTEMS_HPP_
