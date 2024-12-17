/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Join
*/

#ifndef NETWORK_TCP_INCLUDE_COMMANDS_JOIN_HPP_
#define NETWORK_TCP_INCLUDE_COMMANDS_JOIN_HPP_

#include <string>

#include "ACommand.hpp"
#include <nlohmann/json.hpp>

class Join : public ACommand {
public:
  explicit Join(json data);

  void exec_cmd(std::string, asio::ip::tcp::socket &) override;

  ~Join();

protected:
private:
};

#endif  // NETWORK_TCP_INCLUDE_COMMANDS_JOIN_HPP_
