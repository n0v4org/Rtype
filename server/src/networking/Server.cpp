/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Server
*/

#include "networking/Server.hpp"

namespace rtype {
    namespace net {
        Server::Server(int port, bool debug)
        : _port(port), _debug(debug)
        {
        }

        Server::~Server()
        {
        }
    } // namespace net
} // namespace rtype

