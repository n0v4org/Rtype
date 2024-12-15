/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** ICommand
*/

#ifndef NETWORK_TCP_INCLUDE_COMMANDS_ICOMMAND_HPP_
#define NETWORK_TCP_INCLUDE_COMMANDS_ICOMMAND_HPP_

#include <string>
#include <asio.hpp>

class ICommand {
public:
  virtual void exec_cmd(std::string, asio::ip::tcp::socket &) = 0;
  virtual std::string get_resp() const                        = 0;
  virtual void set_resp(std::string)                          = 0;
  virtual bool parse_input(std::string input)                 = 0;
  virtual ~ICommand()                                         = default;

protected:
private:
};

#endif  // NETWORK_TCP_INCLUDE_COMMANDS_ICOMMAND_HPP_
