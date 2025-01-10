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
    inline void handle_server(zef::Engine& engine) {
      while (!engine._server->isQueueEmpty()) {
        input_t rcv = engine._server->popMessage();
        // std::cout << (int)rcv.cmd << std::endl;
      if (rcv.protocol_type == UDP_CMD) {
        int cmdid = static_cast<int>(rcv.cmd);
        if (engine._cmd_map.find(cmdid) != engine._cmd_map.end())
          engine._cmd_map[cmdid](engine, rcv);
      } else {
        std::string cmd_id_tcp = rcv.tcp_cmd; 
        if (engine._cmd_map_tcp.find(cmd_id_tcp) != engine._cmd_map_tcp.end())
          engine._cmd_map_tcp[cmd_id_tcp](engine, rcv);
      }
      }
    }
    inline void handle_client(zef::Engine& engine) {
      // while (!engine._client->isQueueEmpty()) {
      //   input_t rcv = engine._client->popMessage();
      //   // std::cout << (int)rcv.cmd << std::endl;
      //   int cmdid = static_cast<int>(rcv.cmd);
      //   if (engine._cmd_map.find(cmdid) != engine._cmd_map.end())
      //     engine._cmd_map[cmdid](engine, rcv);
      // }
    }
  }  // namespace sys

}  // namespace zef

#endif  // !ENGINE_MODULES_NETWORK_SYSTEMS_HPP_
