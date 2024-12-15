/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** GetAllLobby
*/

#ifndef NETWORK_TCP_INCLUDE_COMMANDS_GETALLLOBBY_HPP_
#define NETWORK_TCP_INCLUDE_COMMANDS_GETALLLOBBY_HPP_

#include <string>
#include "ACommand.hpp"
#include <nlohmann/json.hpp>

class GetAllLobby : public ACommand {
public:
  explicit GetAllLobby(json data);
  void exec_cmd(std::string, asio::ip::tcp::socket &) override;
  ~GetAllLobby();

protected:
private:
};

#endif  // NETWORK_TCP_INCLUDE_COMMANDS_GETALLLOBBY_HPP_
