/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Launch
*/

#ifndef NETWORK_TCP_INCLUDE_COMMANDS_LAUNCH_HPP_
#define NETWORK_TCP_INCLUDE_COMMANDS_LAUNCH_HPP_

#include <string>

#include "ACommand.hpp"
#include <nlohmann/json.hpp>

class Launch : public ACommand {
public:
  explicit Launch(json data);
  void exec_cmd(std::string, asio::ip::tcp::socket &) override;
  ~Launch();

protected:
private:
};

#endif  // NETWORK_TCP_INCLUDE_COMMANDS_LAUNCH_HPP_
