/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_
#include <iostream>
#include <mutex>
#include <deque>
#include <string>
#include <asio.hpp>
#include "Input.hpp"

namespace network {
  namespace tcp_link {

    class Client {
    public:
      input_t popMessage();
      bool isQueueEmpty();
      Client(const std::string& host, const int port,
             asio::io_context& io_service);
      void close() {
        asio::post(io_context_, [this]() { socket_.close(); });
      }
      ~Client();
      void write(const std::string& message) {
        asio::post(io_context_, [this, message]() { send(message); });
      }

      void connect(const std::string& host, const int port) {
        asio::ip::tcp::resolver resolver(io_context_);
        std::cout << "Connecting to " << host << ":" << port << std::endl;
        auto endpoints = resolver.resolve(host, std::to_string(port));

        asio::async_connect(
            socket_, endpoints,
            [this](std::error_code ec, const asio::ip::tcp::endpoint&) {
              if (!ec) {
                std::cout << "Connected to server.\n";
                do_read();
              } else {
                std::cerr << "Connection failed: " << ec.message() << "\n";
              }
            });
      }
      void do_read() {
        asio::async_read_until(
            socket_, asio::dynamic_buffer(read_buffer_), '\n',
            [this](std::error_code ec, std::size_t length) {
              if (!ec) {
                int cmd_len       = 0;
                std::string input = read_buffer_.substr(0, length);
                if (input.find(" ") != std::string::npos)
                  cmd_len = input.find(" ");
                else
                  cmd_len = input.length();

                std::string cmd     = input.substr(0, cmd_len);
                std::string payload = input.substr(cmd_len);
                trim(cmd);
                trim(payload);
                input_t message = {0};
                message.cmd = 0;
                message.payload_size = 0;
                message.seq          = 0;
                message.id           = 0;
                message.payload      = {};

                message.tcp_cmd       = cmd;
                message.tcp_payload   = payload;
                message.protocol_type = TCP_CMD;

                /*input_t message = {
                    .cmd          = 0,
                    .payload_size = 0,
                    .seq          = 0,
                    .id           = 0,
                    .payload      = {},

                    .tcp_cmd       = cmd,
                    .tcp_payload   = payload,
                    .protocol_type = TCP_CMD,
                };*/

                {
                  std::lock_guard<std::mutex> lock(_mutex);
                  _command_queue.push_back(message);
                }
                read_buffer_.erase(0, length);
                do_read();
              } else {
                std::cerr << "Read error: " << ec.message() << "\n";
                socket_.close();
              }
            });
      }

      void send(std::string msg) {
        asio::async_write(socket_, asio::buffer(msg + "\n"),
                          [this](std::error_code ec, std::size_t /*length*/) {
                            if (ec) {
                              std::cerr << "Write error: " << ec.message()
                                        << "\n";
                              socket_.close();
                            }
                          });
      }

      inline void trim(std::string& s) {
        ltrim(s);
        rtrim(s);
      }

      inline void ltrim(std::string& s) {
        s.erase(s.begin(),
                std::find_if(s.begin(), s.end(), [](unsigned char ch) {
                  return !std::isspace(ch);
                }));
      }

      inline void rtrim(std::string& s) {
        s.erase(std::find_if(s.rbegin(), s.rend(),
                             [](unsigned char ch) { return !std::isspace(ch); })
                    .base(),
                s.end());
      }

    protected:
    private:
      asio::io_context& io_context_;
      asio::ip::tcp::socket socket_;
      std::string read_buffer_;
      std::deque<input_t> _command_queue;
      std::mutex _mutex;
    };

  }  // namespace tcp_link
}  // namespace network

#endif /* !CLIENT_HPP_ */
