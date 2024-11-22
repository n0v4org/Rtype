/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Server
*/

#include <iostream>
#include <boost/asio.hpp>
#include <memory>

#include "networking/Server.hpp"

namespace rtype {
namespace net {
Server::Server(int port, bool debug, boost::asio::io_service &io_service) : _port(port), _debug(debug), _socket(io_service, udp::endpoint(udp::v4(), port)) {
    start_receive();
}

void Server::start_receive() {
    _socket.async_receive_from(
        boost::asio::buffer(_recv_buffer_), _remote_endpoint_,
        std::bind(
            &Server::handle_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred
        )    
    );
}

void Server::handle_receive(const std::error_code ec, std::size_t byte_size) {
    if (ec) {
        std::cout << ec << std::endl;
        start_receive();
        return;
    }

    std::shared_ptr<std::string> msg = std::make_shared<std::string>("hello world\n");

    std::cout << "received from " << _remote_endpoint_ << ": " << std::string(_recv_buffer_.data(), byte_size) << " " << byte_size << std::endl;
    _socket.async_send_to(
        boost::asio::buffer(*msg), _remote_endpoint_,
        std::bind(
            &Server::handle_send, this, msg, boost::asio::placeholders::error , boost::asio::placeholders::bytes_transferred
        )
    );
}

void Server::handle_send(std::shared_ptr<std::string>,
      const std::error_code&,
      std::size_t)
  {
    start_receive();
  }

Server::~Server() {
}
}  // namespace net
}  // namespace rtype
