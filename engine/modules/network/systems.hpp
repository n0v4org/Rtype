/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** systems
*/

#ifndef ENGINE_MODULES_NETWORK_SYSTEMS_HPP_
#define ENGINE_MODULES_NETWORK_SYSTEMS_HPP_

#include <string>

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
        std::cout << "salam" << rcv.tcp_cmd << " " << rcv.tcp_payload << std::endl;
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
      while (!engine._client->isQueueEmpty()) {
        input_t rcv = engine._client->popMessage();
        if (rcv.protocol_type == UDP_CMD) {
          int cmdid = static_cast<int>(rcv.cmd);
          if (engine._cmd_map.find(cmdid) != engine._cmd_map.end())
            engine._cmd_map[cmdid](engine, rcv);
        } else {
          std::string cmdtcp = rcv.tcp_cmd + rcv.tcp_payload;
          int status_int = -1;
          std::string status = "";
          nlohmann::json j = nlohmann::json::parse(cmdtcp);
          if (j.contains("status")) {
            status_int = j["status"];
            status = std::to_string(status_int);
            std::cout << "stt: " << status << std::endl;
            rcv.tcp_payload = rcv.tcp_cmd + rcv.tcp_payload;
            
            if (engine._cmd_map_tcp.find(status) != engine._cmd_map_tcp.end())
              engine._cmd_map_tcp[status](engine, rcv);
          }
        }
      }
    }
  }  // namespace sys

}  // namespace zef

#endif  // !ENGINE_MODULES_NETWORK_SYSTEMS_HPP_
