/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** TcpClient
*/

#include "networking/TcpClient.hpp"
#include "ClientError.hpp"

#include <iostream>

namespace client {
    namespace net{
TcpClient::TcpClient(int server_port, int client_port, std::string ip, asio::io_context &context)
: _socket(context, tcp::endpoint(tcp::v4(), client_port))
      , _io_service(context)
{
        asio::error_code ec;
        tcp::endpoint endpoint(asio::ip::address::from_string(ip), server_port);
        _socket.connect(endpoint, ec);
        if (ec) {
            std::cerr << "Connection failed: " << ec.message() << std::endl;
        } else {
            std::cout << "Successfully connected to " << ip << ":" << server_port << std::endl;
        }
}

void TcpClient::close_connection() {
    _socket.close();
}

void TcpClient::send(const std::string &msg) {
    asio::write(_socket, asio::buffer(msg));
}

TcpClient::~TcpClient()
{
}
    }
}