/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** FactoryCmd
*/

#ifndef NETWORK_TCP_INCLUDE_COMMANDS_FACTORYCMD_HPP_
#define NETWORK_TCP_INCLUDE_COMMANDS_FACTORYCMD_HPP_
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include "ACommand.hpp"
#include "Join.hpp"

using json            = nlohmann::json;
using FactoryFunction = std::function<std::shared_ptr<ICommand>()>;

class FactoryCmd {
public:
  static FactoryCmd& getInstance() {
    static FactoryCmd instance;
    return instance;
  }

  void registerAllCommand();
  void registerCommand(const std::string&, FactoryFunction);
  std::shared_ptr<ICommand> createCmd(const std::string& name) const;

protected:
private:
  std::unordered_map<std::string, FactoryFunction> _map;
  FactoryCmd()                             = default;
  FactoryCmd(const FactoryCmd&)            = delete;
  FactoryCmd& operator=(const FactoryCmd&) = delete;
};

#endif  // NETWORK_TCP_INCLUDE_COMMANDS_FACTORYCMD_HPP_
