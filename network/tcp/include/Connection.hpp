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
#include <iostream>
#include <asio.hpp>
#include "Commands/FactoryCmd.hpp"

using asio::ip::tcp;

static const char CMD_NOT_FOUND[] = "500 cmd not found";

namespace network {
  namespace lobby {
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

      void handle_read(const std::error_code& /*error*/,
                       size_t bytes_transferred) {
        try {
          std::string input(_data, bytes_transferred);
          int cmd_len = 0;
          if (input.find(" ") != std::string::npos)
            cmd_len = input.find(" ");
          else
            cmd_len = input.length();

          std::string cmd = input.substr(0, cmd_len);
          ltrim(cmd);
          rtrim(cmd);
          auto _factoryCmd = FactoryCmd::getInstance().createCmd(cmd);
          _factoryCmd->exec_cmd(input.substr(cmd_len, input.length() - cmd_len),
                                socket());
          write(_factoryCmd->get_resp());
        } catch (const std::invalid_argument& e) {
          write(CMD_NOT_FOUND);
        }
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
    };
  }  // namespace lobby
}  // namespace network

#endif  // NETWORK_TCP_INCLUDE_CONNECTION_HPP_
