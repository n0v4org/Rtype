/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Client
*/

#ifndef SERVER_INCLUDE_NETWORKING_CLIENT_HPP_
#define SERVER_INCLUDE_NETWORKING_CLIENT_HPP_
#include <asio.hpp>

using asio::ip::udp;

namespace rtype {
  namespace net {
    class Client {
    public:
      void operator()(udp::endpoint);

    protected:
    private:
      udp::endpoint _client_endpoint;
    };
  }  // namespace net
}  // namespace rtype

#endif  // SERVER_INCLUDE_NETWORKING_CLIENT_HPP_
