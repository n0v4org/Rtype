/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Server
*/

#ifndef SERVER_INCLUDE_NETWORKING_SERVER_HPP_
#define SERVER_INCLUDE_NETWORKING_SERVER_HPP_
#include <string>
#include <map>
#include <thread>
#include <boost/asio.hpp>
#include "macro.hpp"

using boost::asio::ip::udp;

namespace rtype {
  namespace net {
    class Server {
    public:
      Server(int, bool, boost::asio::io_service &);
      void close_connection();
      ~Server();

    protected:
    private:
      void start_receive();
      void dispatch_client(const std::error_code, std::size_t);
      void handle_send(std::shared_ptr<std::string>, const std::error_code &,
                       std::size_t);
      void unpack(std::size_t);
      int _port;
      bool _debug;
      udp::socket _socket;
      std::map<udp::endpoint, std::thread> _clients;
      std::array<uint8_t, BUFFER_SIZE> _recv_buffer_;
      udp::endpoint _remote_endpoint_;
    };
  }  // namespace net
}  // namespace rtype

#endif  // SERVER_INCLUDE_NETWORKING_SERVER_HPP_
