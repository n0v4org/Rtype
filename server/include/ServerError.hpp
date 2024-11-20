/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** ServerError
*/

#ifndef SERVER_INCLUDE_SERVERERROR_HPP_
#define SERVER_INCLUDE_SERVERERROR_HPP_
#include <map>
#include <string>

enum {
    SERVER_INTERNAL_ERROR = 0,
    ARGS_ERROR = 1,
};

static const std::map<int, std::string> ERRORS = {
    {SERVER_INTERNAL_ERROR, "Internal Server Error: "},
    {ARGS_ERROR, "Error while parsing command line arguments: "}
};

enum Color { RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN };

static const std::map<int, std::string> COLORS = {
    {RED, "\033[31m"},  {GREEN, "\033[32m"},   {YELLOW, "\033[33m"},
    {BLUE, "\033[34m"}, {MAGENTA, "\033[35m"}, {CYAN, "\033[36m"},
};

static const char RESET_COLOR[5] = "\033[0m";

class ServerError : public std::exception {
public:
  ServerError(std::string msg, int type) {
    if (ERRORS.find(type) != ERRORS.end()) {
      _msg = COLORS.at(RED) + ERRORS.at(type) + RESET_COLOR + COLORS.at(GREEN) +
             msg + RESET_COLOR;
    } else {
      _msg = "Unknown Error: " + msg;
    }
  }
  const char* what() const noexcept override {
    return _msg.c_str();
  }

protected:
private:
  std::string _msg;
};

#endif /* SERVER_INCLUDE_SERVERERROR_HPP_ */
