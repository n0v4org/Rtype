/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** FactoryCmd
*/

#include <fstream>
#include <iostream>
#include <filesystem>

#include <nlohmann/json.hpp>
#include "Commands/FactoryCmd.hpp"

static const char CONFIG_FILE[] = "network/tcp/conf/cmd.json";

void FactoryCmd::registerAllCommand() {
    std::ifstream jsonFile(CONFIG_FILE);
    json data = json::parse(jsonFile);

 
   _map["JOIN"] = [data]() { return std::make_shared<Join>(data["JOIN"]);};

    jsonFile.close();
}

void FactoryCmd::registerCommand(const std::string& name, FactoryFunction creator) {
        _map[name] = creator;
}

std::shared_ptr<ICommand> FactoryCmd::createCmd(const std::string &name) const
{
    auto it = _map.find(name);
    if (it != _map.end()) {
        return it->second();
    } else {
        throw std::invalid_argument("cmd type not found: " + name);
    }
}
