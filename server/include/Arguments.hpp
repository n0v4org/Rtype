/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Arguments
*/

#ifndef SERVER_INCLUDE_ARGUMENTS_HPP_
#define SERVER_INCLUDE_ARGUMENTS_HPP_
#include <map>
#include <string>
#include <vector>
#include <array>

namespace rtype {

  static const std::array<std::string, 4> FLAGS = {
      "-gp",
      "-lp",
      "-h",
      "-v",
  };

  enum {
    GAME_PORT  = 0,
    LOBBY_PORT = 1,
    HELP       = 2,
    DEBUG      = 3,
  };

  class Arguments {
  public:
    Arguments(int, char *[]);
    Arguments(int, const char *[]);
    void parse();
    int get_game_port() const;
    int get_lobby_port() const;
    bool get_help() const;
    bool get_debug() const;
    ~Arguments();

  protected:
  private:
    bool is_number(std::string);
    std::vector<std::string> _args;
    bool _help;
    bool _debug;
    int _game_port;
    int _lobby_port;
  };

}  // namespace rtype

#endif  // SERVER_INCLUDE_ARGUMENTS_HPP_
