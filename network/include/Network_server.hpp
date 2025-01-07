/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Network_server
*/

#ifndef Network_server_HPP_
#define Network_server_HPP_
#include <thread>
#include <memory>
#include <asio.hpp>
#include "../udp/include/Server.hpp"
#include "../tcp/include/Server.hpp"

namespace network {

class Network_server {
    public:
        Network_server(int, int);
        std::shared_ptr<game::Server> get_udp_server() const;
        std::shared_ptr<tcp_link::Server> get_tcp_server() const;
        input_t popMessage();
        bool isQueueEmpty();
        ~Network_server();

    protected:
    private:
      std::shared_ptr<game::Server> _server_udp;
      std::shared_ptr<tcp_link::Server> _server_tcp;
      asio::io_context _io_service;
      std::thread t;
};
}  // namespace Network_server

#endif /* !Network_server_HPP_ */
