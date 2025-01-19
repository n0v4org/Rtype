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
#include <unordered_set>
#include <mutex>
#include <vector>
#include <asio.hpp>
#include "IServer.hpp"
#include "Input.hpp"
#include "Commands.hpp"

using asio::ip::udp;

namespace network {
  namespace game {

    class Server : public IServer {
    public:
      Server(asio::io_context& context, int port);

      void close_connection();
      input_t popMessage();
      bool isQueueEmpty();

      template <typename T>
      void send(int idx, int cmd, const T& payload) {
        std::array<uint8_t, 1024> message =
            Commands<T>::toArray(payload, cmd, _sequence_id);

        std::vector<uint8_t> temp(message.begin(), message.end());
        temp.resize(sizeof(T) + 7);
        std::vector<uint8_t> compressed_message = compressVector(temp);

        std::vector<uint8_t> header(4 + compressed_message.size());
        uint32_t compressed_size = sizeof(T) + 7;
        header[0] = static_cast<uint8_t>((compressed_size >> 24) & 0xFF);
        header[1] = static_cast<uint8_t>((compressed_size >> 16) & 0xFF);
        header[2] = static_cast<uint8_t>((compressed_size >> 8) & 0xFF);
        header[3] = static_cast<uint8_t>(compressed_size & 0xFF);

        std::memcpy(header.data() + 4, compressed_message.data(),
                    compressed_message.size());
        for (int i = 0; i < 10; i++) {
          _socket.async_send_to(
              asio::buffer(header), _clients[idx],
              [this](const std::error_code& ec, std::size_t bytes_transferred) {
                handle_send(ec, bytes_transferred);
              });
        }
        _sequence_id++;
      }

      std::vector<int> getAllIds();

    private:
      void start_receive();
      void dispatch_client(const std::error_code& ec,
                           std::size_t bytes_transferred);
      void handle_send(const std::error_code& ec,
                       std::size_t bytes_transferred);

      udp::socket _socket;
      udp::endpoint _remote_endpoint_;
      std::array<uint8_t, 1024> _recv_buffer_;
      std::deque<input_t> _command_queue;
      std::vector<udp::endpoint> _clients;
      bool is_registered();
      std::mutex _mutex;
      int _sequence_id;
      bool _debug;
      std::unordered_set<uint32_t> _read_id;
    };

  }  // namespace game
}  // namespace network

#endif  // NETWORK_UDP_INCLUDE_SERVER_HPP_