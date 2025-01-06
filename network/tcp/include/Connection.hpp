/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Tcp
*/

#ifndef NETWORK_TCP_INCLUDE_CONNECTION_HPP_
#define NETWORK_TCP_INCLUDE_CONNECTION_HPP_

#include <string>
#include <memory>
#include <mutex>
#include <deque>
#include <iostream>
#include <asio.hpp>
#include "Input.hpp"
#include "queue.hpp"
#include "Commands/FactoryCmd.hpp"

using asio::ip::tcp;

static const char CMD_NOT_FOUND[] = "500 cmd not found";

namespace network {
  namespace tcp_link {

    class Connection : public std::enable_shared_from_this<Connection> {
    public:
      typedef std::shared_ptr<Connection> pointer;

      static pointer create(asio::io_context& io_context) {
        return pointer(new Connection(io_context));
      }

      tcp::socket& socket() {
        return socket_;
      }

      void write(std::string msg) {
        asio::async_write(
            socket_, asio::buffer(msg + "\n"),
            std::bind(&Connection::handle_write, shared_from_this(),
                      asio::placeholders::error,
                      asio::placeholders::bytes_transferred));
      }

      void start() {
        write("200");
      }

      void assign_id(int id) {
        _id = id;
      }

    private:
      explicit Connection(asio::io_context& io_context) : socket_(io_context) {
      }

      void read() {
        socket_.async_read_some(
            asio::buffer(_data, 1024),
            std::bind(&Connection::handle_read, shared_from_this(),
                      asio::placeholders::error,
                      asio::placeholders::bytes_transferred));
      }

      void handle_write(const std::error_code& /*error*/,
                        size_t bytes_transferred) {
        read();
      }

      void handle_read(const std::error_code& ec/*error*/,
                       size_t bytes_transferred) {
        try {
          std::string input(_data, bytes_transferred);
          if (ec) {
            std::cerr << "Error reading from socket: " << ec.message()
                      << std::endl;
            return;
          }
          int cmd_len = 0;
          if (input.find(" ") != std::string::npos)
            cmd_len = input.find(" ");
          else
            cmd_len = input.length();

          std::string cmd = input.substr(0, cmd_len);
          std::string payload =  input.substr(cmd_len);
          trim(cmd);
          trim(payload);

          input_t message = {
            .protocol_type = TCP_CMD,
            .tcp_cmd = cmd,
            .tcp_payload = payload,
            .id = _id,
          };
          {
          std::lock_guard<std::mutex> lock(_mutex);
          tcp_command_queue.push_back(message);
        }
          read();
        } catch (const std::invalid_argument& e) {
          write(CMD_NOT_FOUND);
        }
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
      asio::ip::tcp::socket socket_;
      std::string message_;
      char _data[1024];
      int _id;
    };
  }  // namespace tcp_link
}  // namespace network

#endif  // NETWORK_TCP_INCLUDE_CONNECTION_HPP_
