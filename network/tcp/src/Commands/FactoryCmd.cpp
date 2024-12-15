/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** FactoryCmd
*/

#include <fstream>
#include <memory>
#include <string>
#include <iostream>

#include <nlohmann/json.hpp>
#include "Commands/FactoryCmd.hpp"
#include "Commands/GetAllLobby.hpp"
#include "Commands/GetLobby.hpp"
#include "Commands/Launch.hpp"

static const char CONFIG_FILE[] = "network/tcp/conf/cmd.json";

void FactoryCmd::registerAllCommand() {
  std::ifstream jsonFile(CONFIG_FILE);
  json data = json::parse(jsonFile);

  _map["JOIN"] = [data]() { return std::make_shared<Join>(data["JOIN"]); };
  _map["GET_ALL_LOBBY"] = [data]() {
    return std::make_shared<GetAllLobby>(data["GET_ALL_LOBBY"]);
  };
  _map["GET_LOBBY"] = [data]() {
    return std::make_shared<GetLobby>(data["GET_LOBBY"]);
  };
  _map["LAUNCH_GAME"] = [data]() {
    return std::make_shared<Launch>(data["LAUNCH_GAME"]);
  };

  jsonFile.close();
}

void FactoryCmd::registerCommand(const std::string &name,
                                 FactoryFunction creator) {
  _map[name] = creator;
}

std::shared_ptr<ICommand> FactoryCmd::createCmd(const std::string &name) const {
  auto it = _map.find(name);
  if (it != _map.end()) {
    return it->second();
  } else {
    throw std::invalid_argument("cmd type not found: " + name);
  }
}
