/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Arguments
*/

#include <iostream>
#include <string>
#include <random>

#include "ClientError.hpp"
#include "Arguments.hpp"
#include "macro.hpp"

static int MAX_PORT                     = 65535;
static int MIN_PORT                     = 1024;
static const char UNKNOWN_FLAG[33]      = "unknown flag, args not processes";
static const char BAD_PORT[22]          = "port must be a number";
static const char PORT_OUT_OF_RANGE[36] = "port must be between 1024 and 65535";
static const char EMPTY_FLAG[20]        = "found an empty flag";
static const char INAVLID_IP[19]        = "invalid IP address";

namespace client {

  Arguments::Arguments(int argc, char *argv[])
    : _help(false)
    , _ip(SERVER_ADDRESS)
    , _client_port(PORT_CLIENT)
    , _server_port(PORT_SERVER)
    , _lobby_client_port(generateRandomPort())
    , _lobby_server_port(LOBBY_PORT_SERVER) {
    for (int i = 1; i < argc; i++) _args.push_back(argv[i]);
  }

  Arguments::Arguments(int argc, const char *argv[])
    : _help(false)
    , _ip(SERVER_ADDRESS)
    , _client_port(PORT_CLIENT)
    , _server_port(PORT_SERVER)
    , _lobby_client_port(LOBBY_PORT_CLIENT)
    , _lobby_server_port(LOBBY_PORT_SERVER) {
    for (int i = 1; i < argc; i++) _args.push_back(argv[i]);
  }

  int Arguments::generateRandomPort() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1024, 65535);

    return distr(gen);
  }

  bool Arguments::is_number(std::string str) {
    std::string::const_iterator it = str.begin();

    for (; it != str.end() && std::isdigit(*it); ++it)
      ;
    if (it == str.end())
      return true;
    return false;
  }

  bool Arguments::is_valid_ip(std::string str) {
    std::string::const_iterator it = str.begin();

    for (; it != str.end() && (std::isdigit(*it) || *it == '.' || *it == '/');
         ++it)
      ;
    if (it == str.end())
      return true;
    return false;
  }

  void Arguments::parse() {
    int current = -1;

    for (auto &i : _args) {
      if (current != -1) {
        for (int j = 0; j < FLAGS.size(); j++) {
          if (FLAGS[j] == i) {
            throw ClientError(EMPTY_FLAG, ARGS_ERROR);
          }
        }
        switch (current) {
          case SERVER_PORT:
            if (!is_number(i))
              throw ClientError(BAD_PORT, ARGS_ERROR);
            _server_port = std::stoi(i);
            if (_server_port < MIN_PORT || _server_port > MAX_PORT)
              throw ClientError(PORT_OUT_OF_RANGE, ARGS_ERROR);
            break;

          case CLIENT_PORT:
            if (!is_number(i))
              throw ClientError(BAD_PORT, ARGS_ERROR);
            _client_port = std::stoi(i);
            if (_client_port < MIN_PORT || _client_port > MAX_PORT)
              throw ClientError(PORT_OUT_OF_RANGE, ARGS_ERROR);
            break;

          case SERVER_LOBBY_PORT:
            if (!is_number(i))
              throw ClientError(BAD_PORT, ARGS_ERROR);
            _lobby_server_port = std::stoi(i);
            if (_lobby_server_port < MIN_PORT || _lobby_server_port > MAX_PORT)
              throw ClientError(PORT_OUT_OF_RANGE, ARGS_ERROR);
            break;

          case CLIENT_LOBBY_PORT:
            if (!is_number(i))
              throw ClientError(BAD_PORT, ARGS_ERROR);
            _lobby_client_port = std::stoi(i);
            if (_lobby_client_port < MIN_PORT || _lobby_client_port > MAX_PORT)
              throw ClientError(PORT_OUT_OF_RANGE, ARGS_ERROR);
            break;

          case IP:
            if (!is_valid_ip(i))
              throw ClientError(INAVLID_IP, ARGS_ERROR);
            _ip = i;
            break;

          default:
            throw ClientError(EMPTY_FLAG, ARGS_ERROR);
            break;
        }
        current = -1;
        continue;
      }
      for (int j = 0; j < FLAGS.size(); j++) {
        if (FLAGS[j] == i) {
          current = j;
          break;
        }
      }
      if (current == -1) {
        throw ClientError(UNKNOWN_FLAG, ARGS_ERROR);
      }
      if (current == HELP) {
        _help   = true;
        current = -1;
      }
    }
    if (current != -1) {
      throw ClientError(EMPTY_FLAG, ARGS_ERROR);
    }
  }

  int Arguments::get_server_port() const {
    return _server_port;
  }

  int Arguments::get_client_port() const {
    return _client_port;
  }

  int Arguments::get_lobby_server_port() const {
    return _lobby_server_port;
  }
  int Arguments::get_lobby_client_port() const {
    return _lobby_client_port;
  }

  bool Arguments::get_help() const {
    return _help;
  }

  std::string Arguments::get_ip() const {
    return _ip;
  }

  Arguments::~Arguments() {
  }

}  // namespace client
