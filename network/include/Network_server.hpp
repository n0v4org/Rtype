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
#include <vector>
#include <asio.hpp>
#include "../udp/include/Server.hpp"
#include "../tcp/include/Server.hpp"

static const int DEFAULT_LOBBY_ID = -1;

namespace network {

  class Network_server {
  public:
    Network_server(int);
    std::shared_ptr<game::Server> get_udp_server(int idx) const;
    std::shared_ptr<tcp_link::Server> get_tcp_server(int idx) const;
    std::shared_ptr<tcp_link::Server> get_lobby() const;
    int set_new_game(int udp_port, int tcp_port);
    input_t popMessage(int idx);
    bool isQueueEmpty(int idx);
    ~Network_server();  

  protected:
  private:
    std::shared_ptr<game::Server> _server_udp;
    std::shared_ptr<tcp_link::Server> _server_tcp;
    std::vector<std::shared_ptr<tcp_link::Server>> _servers_tcp;
    std::vector<std::shared_ptr<game::Server>> _servers_udp;
    std::shared_ptr<tcp_link::Server> _lobby;
    asio::io_context _io_service;
    std::thread t;
  };
}  // namespace network

#endif /* !Network_server_HPP_ */
