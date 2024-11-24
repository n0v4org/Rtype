/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Arguments
*/

#ifndef CLIENT_INCLUDE_ARGUMENTS_HPP_
#define CLIENT_INCLUDE_ARGUMENTS_HPP_
#include <map>
#include <string>
#include <vector>

namespace client {

  static const std::vector<std::string> FLAGS = {
      "-p",
      "-h",
      "-ip",
  };

  enum {
    PORT = 0,
    HELP = 1,
    IP   = 2,
  };

  class Arguments {
  public:
    Arguments(int, char *[]);
    Arguments(int, const char *[]);
    void parse();
    int get_port() const;
    bool get_help() const;
    std::string get_ip() const;
    ~Arguments();

  protected:
  private:
    bool is_number(std::string);
    std::vector<std::string> _args;
    bool _help;
    int _port;
    std::string _ip;
  };

}  // namespace client

#endif  // CLIENT_INCLUDE_ARGUMENTS_HPP_
