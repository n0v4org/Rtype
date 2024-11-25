/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Client
*/

#ifndef CLIENT_INCLUDE_NETWORKING_CLIENT_HPP_
#define CLIENT_INCLUDE_NETWORKING_CLIENT_HPP_
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

namespace client {
  namespace net {

    class Client {
    public:
      Client(int, int, std::string, boost::asio::io_service &);
      void run();
      ~Client();

    protected:
    private:
      udp::socket _socket;
      boost::asio::io_service& _io_service;
    };

  }  // namespace net
}  // namespace client

#endif  // CLIENT_INCLUDE_NETWORKING_CLIENT_HPP_
