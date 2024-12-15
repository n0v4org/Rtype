/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Arguments
*/

#include <iostream>
#include <string>

#include "Arguments.hpp"
#include "ServerError.hpp"
#include "macro.hpp"

static int MAX_PORT                     = 65535;
static int MIN_PORT                     = 1024;
static const char UNKNOWN_FLAG[33]      = "unknown flag, args not processes";
static const char BAD_PORT[22]          = "port must be a number";
static const char PORT_OUT_OF_RANGE[36] = "port must be between 1024 and 65535";
static const char EMPTY_FLAG[20]        = "found an empty flag";

namespace rtype {

  Arguments::Arguments(int argc, char *argv[])
    : _help(false)
    , _debug(false)
    , _game_port(PORT_GAME)
    , _lobby_port(PORT_LOBBY) {
    for (int i = 1; i < argc; i++) _args.push_back(argv[i]);
  }

  Arguments::Arguments(int argc, const char *argv[])
    : _help(false)
    , _debug(false)
    , _game_port(PORT_GAME)
    , _lobby_port(PORT_LOBBY) {
    for (int i = 1; i < argc; i++) _args.push_back(argv[i]);
  }

  bool Arguments::is_number(std::string str) {
    std::string::const_iterator it = str.begin();

    for (; it != str.end() && std::isdigit(*it); ++it)
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
            throw ServerError(EMPTY_FLAG, ARGS_ERROR);
          }
        }
        switch (current) {
          case GAME_PORT:
            if (!is_number(i))
              throw ServerError(BAD_PORT, ARGS_ERROR);
            _game_port = std::stoi(i);
            if (_game_port < MIN_PORT || _game_port > MAX_PORT)
              throw ServerError(PORT_OUT_OF_RANGE, ARGS_ERROR);
            break;

          case LOBBY_PORT:
            if (!is_number(i))
              throw ServerError(BAD_PORT, ARGS_ERROR);
            _lobby_port = std::stoi(i);
            if (_lobby_port < MIN_PORT || _lobby_port > MAX_PORT)
              throw ServerError(PORT_OUT_OF_RANGE, ARGS_ERROR);
            break;

          default:
            throw ServerError(EMPTY_FLAG, ARGS_ERROR);
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
        throw ServerError(UNKNOWN_FLAG, ARGS_ERROR);
      }
      if (current == HELP) {
        _help   = true;
        current = -1;
      }
      if (current == DEBUG) {
        _debug  = true;
        current = -1;
      }
    }
    if (current != -1) {
      throw ServerError(EMPTY_FLAG, ARGS_ERROR);
    }
  }

  int Arguments::get_game_port() const {
    return _game_port;
  }

  int Arguments::get_lobby_port() const {
    return _lobby_port;
  }

  bool Arguments::get_help() const {
    return _help;
  }

  bool Arguments::get_debug() const {
    return _debug;
  }

  Arguments::~Arguments() {
  }

}  // namespace rtype
