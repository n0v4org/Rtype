/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Client
*/

#include "networking/Client.hpp"

#include <iostream>

#include <boost/asio.hpp>

namespace rtype {
  namespace net {

    void Client::operator()(udp::endpoint endpoint) {
      std::cout << "in operator " << endpoint << std::endl;
      _client_endpoint = endpoint;
    }

  }  // namespace net
}  // namespace rtype