/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Network_client
*/

#ifndef NETWORK_CLIENT_HPP_
#define NETWORK_CLIENT_HPP_

#include <memory>
#include <string>
#include <mutex>
#include <thread>
#include <asio.hpp>
#include "Client.hpp"
#include "../tcp/include/Client.hpp"

namespace network {

  class Network_client {
  public:
    Network_client(int, int, int, std::string);
    std::shared_ptr<game::Client> get_udp_client() const;
    std::shared_ptr<tcp_link::Client> get_tcp_client() const;
    input_t popMessage();
    bool isQueueEmpty();
    void reset_clients(int server_port, int client_port, int lobby_port,
                       std::string ip);
    ~Network_client();

  protected:
  private:
    std::shared_ptr<game::Client> _client_udp;
    std::shared_ptr<tcp_link::Client> _client_tcp;
    std::mutex reset_mutex;
    asio::io_context _io_service;
    std::thread t;
  };
}  // namespace network

#endif /* !NETWORK_CLIENT_HPP_ */
