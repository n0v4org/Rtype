/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** ClientError
*/

#ifndef CLIENT_INCLUDE_CLIENTERROR_HPP_
#define CLIENT_INCLUDE_CLIENTERROR_HPP_
#include <cstring>
#include <map>
#include <string>

enum {
  CLIENT_INTERNAL_ERROR = 0,
  ARGS_ERROR            = 1,
};

static const std::map<int, std::string> ERRORS = {
    {CLIENT_INTERNAL_ERROR, "Internal Client Error: "},
    {ARGS_ERROR, "Error while parsing command line arguments: "}};

enum Color { RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN };

static const std::map<int, std::string> COLORS = {
    {RED, "\033[31m"},  {GREEN, "\033[32m"},   {YELLOW, "\033[33m"},
    {BLUE, "\033[34m"}, {MAGENTA, "\033[35m"}, {CYAN, "\033[36m"},
};

static const char RESET_COLOR[5] = "\033[0m";

class ClientError : public std::exception {
    public:
        ClientError(std::string msg, int type) {
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

#endif // CLIENT_INCLUDE_CLIENTERROR_HPP_
