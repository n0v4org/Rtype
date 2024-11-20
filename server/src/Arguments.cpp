/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Arguments
*/

#include <iostream>

#include "Arguments.hpp"
#include "ServerError.hpp"

static int MAX_PORT = 65535;
static int MIN_PORT = 1024;
static const char UNKNOWN_FLAG[33] = "unknown flag, args not processes";
static const char BAD_PORT[22] = "port must be a number";
static const char PORT_OUT_OF_RANGE[36] = "port must be between 1024 and 65535";

Arguments::Arguments(int argc, char *argv[])
: _help(false), _debug(false), _port(50000)
{
    for (int i = 1; i < argc; i++)
        _args.push_back(argv[i]);
}

bool Arguments::is_number (std::string str) {
    std::string::const_iterator it = str.begin();

    for (; it != str.end() && std::isdigit(*it); ++it);
    if (it == str.end())
        return true;
    return false;
}

void Arguments::parse()
{
    int current = -1;

    for (auto &i: _args) {
        if (current != -1) {
            switch (current)
            {
            case PORT:
                if (!is_number(i))
                    throw ServerError(BAD_PORT, ARGS_ERROR);
                _port = std::stoi(i);
                if (_port < MIN_PORT || _port > MAX_PORT)
                    throw ServerError(PORT_OUT_OF_RANGE, ARGS_ERROR);
                break;
            
            default:
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
            _help = true;
            current = -1;
        }
        if (current == DEBUG) {
            _debug = true;
            current = -1;
        }
    }
}

int Arguments::get_port() const
{
    return _port;
}

bool Arguments::get_help() const
{
    return _help;
}

bool Arguments::get_debug() const
{
    return _debug;
}

Arguments::~Arguments()
{
}