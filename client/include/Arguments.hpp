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
#include <array>

namespace client {

  static const std::array<std::string, 6> FLAGS = {
      "-sp",
      "-cp",
      "-h",
      "-ip",
      "-lsp",
      "-lcp"
  };

  enum {
    SERVER_PORT = 0,
    CLIENT_PORT = 1,
    HELP        = 2,
    IP          = 3,
    SERVER_LOBBY_PORT = 4,
    CLIENT_LOBBY_PORT = 5
  };

  class Arguments {
  public:
    Arguments(int, char *[]);
    Arguments(int, const char *[]);
    void parse();
    int get_server_port() const;
    int get_client_port() const;
    int get_lobby_server_port() const;
    int get_lobby_client_port() const;
    bool get_help() const;
    std::string get_ip() const;
    ~Arguments();

  protected:
  private:
    bool is_number(std::string);
    bool is_valid_ip(std::string);
    std::vector<std::string> _args;
    bool _help;
    int _server_port;
    int _client_port;
    int _lobby_server_port;
    int _lobby_client_port;
    std::string _ip;
  };

}  // namespace client

#endif  // CLIENT_INCLUDE_ARGUMENTS_HPP_
