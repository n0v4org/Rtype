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
#include "Server.hpp"

namespace network {

class Network_server {
    public:
        Network_server(int);
        std::shared_ptr<game::Server> get_udp_server() const;
        ~Network_server();

    protected:
    private:
      std::shared_ptr<game::Server> _server_udp;
      asio::io_context _io_service;
      std::thread t;
};
}  // namespace Network_server

#endif /* !Network_server_HPP_ */
