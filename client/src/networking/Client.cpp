/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Client
*/

#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include "networking/Client.hpp"

using boost::asio::ip::udp;

namespace client {
  namespace net {

    Client::Client(int server_port, int client_port, std::string ip,
                   boost::asio::io_service &service)
      : _socket(service, udp::endpoint(udp::v4(), client_port)), _io_service(service) {
      udp::resolver resolver(_io_service);
      udp::resolver::query query(udp::v4(), ip, std::to_string(server_port));
      udp::resolver::iterator iter = resolver.resolve(query);
      _server_endpoint             = *iter;
      _recv_thread = std::thread(&Client::recv_thread, this);

    }

    void Client::send(const std::string &msg) {
      _socket.send_to(boost::asio::buffer(msg), _server_endpoint);
    }

    void Client::close_connection() {
      _socket.close();
    }

    void Client::startReceive() {
      while (1) {
        udp::endpoint remote_endpoint;
        boost::system::error_code error;
        int byteReceived = _socket.receive_from(boost::asio::buffer(_recvBuffer),
            remote_endpoint, 0, error);
        std::cout << "received : " << std::string(_recvBuffer.data(), byteReceived) << std::endl;
        if (error && error != boost::asio::error::message_size)
          throw boost::system::system_error(error);
      }
    }

    void Client::recv_thread() {
      try
      {
        startReceive();
      }
      catch(const std::exception& e)
      {
        std::cerr << e.what() << '\n';
      } 
    }

    Client::~Client() {
    }

  }  // namespace net
}  // namespace client
