/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** UdpProtoCommands
*/

#ifndef UDPPROTOCOMMANDS_HPP_
#define UDPPROTOCOMMANDS_HPP_

enum {
    LOGIN = 0,
};

enum {
    PWD_ERRORS = 40,
};

//Commands

struct login_t {
    char pwd[21];
};

//Errors

struct pwd_error_t {
    char error[13];
};

#endif /* !UDPPROTOCOMMANDS_HPP_ */
