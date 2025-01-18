/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** tcp_cmds
*/

#ifndef TCP_CMDS_HPP_
#define TCP_CMDS_HPP_

#include <thread>
#include <vector>
#include <string>
#include <utility>
#include <array>
#include <map>

enum {
  GAME_SUCCESS = 0,
  GAME_NB_ARGS = 1,
  GAME_STATUS  = 2,
};

enum {
  GAME_INVALID_ARGS = 0,
  WRONG_PWD         = 1,
};

static const char LOGIN_CMD[]      = "LOGIN";
static const char START_GAME_CMD[] = "START";

static const uint16_t GAME_NB_TCP_CMD    = 3;
static const uint16_t GAME_NB_TCP_ERRORS = 2;

static const std::array<std::pair<int, std::string>, GAME_NB_TCP_ERRORS>
    GAME_TCP_ERRORS = {{{420, "invalid args"}, {421, "invalid login code"}}};

static const std::map<std::string, std::array<std::string, GAME_NB_TCP_CMD>>
    CMD_TCP_RES = {{LOGIN_CMD, {"successfully logged in for tcp", "1", "220"}},
                   {START_GAME_CMD, {"game is starting", "0", "221"}}};

#endif /* !TCP_CMDS_HPP_ */
