/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Server
*/

#ifndef NETWORK_UDP_INCLUDE_SERVER_HPP_
#define NETWORK_UDP_INCLUDE_SERVER_HPP_

#include <map>
#include <memory>
#include <thread>
#include <deque>
#include <mutex>
#include <asio.hpp>
#include "Input.hpp"
#include "Commands.hpp"

using asio::ip::udp;

namespace network {
    namespace game {

class Server {
public:
    Server(asio::io_context& context, int port);

    void close_connection();
    input_t popMessage();
    bool isQueueEmpty();

    void send(const udp::endpoint& client, std::array<uint8_t, 1024> message);
    ~Server();

private:
    void start_receive();
    void dispatch_client(const std::error_code& ec, std::size_t bytes_transferred);
    void handle_send(const std::error_code& ec, std::size_t bytes_transferred);

    udp::socket _socket;
    udp::endpoint _remote_endpoint_;
    std::array<uint8_t, 1024> _recv_buffer_;
    std::deque<input_t> _command_queue;
    std::mutex _mutex;
    bool _debug;
};

    } // namespace game
} // namespace network

#endif // NETWORK_UDP_INCLUDE_SERVER_HPP_