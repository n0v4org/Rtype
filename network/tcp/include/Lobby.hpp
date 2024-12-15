/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Lobby
*/

#ifndef SERVER_INCLUDE_NETWORKING_LOBBY_HPP_
#define SERVER_INCLUDE_NETWORKING_LOBBY_HPP_
#include <asio.hpp>
#include <vector>
#include <array>
#include <iostream>
#include <deque>
#include "Connection.hpp"
#include "Commands/FactoryCmd.hpp"
#include "Commands/ACommand.hpp"

extern std::array<std::vector<asio::ip::tcp::endpoint>, 5> LOBBY;

using asio::ip::tcp;

  namespace network {
    namespace lobby {

class Server {
  public:
      Server(int, bool, asio::io_context&);

  private:
    void start_accept();
    void handle_accept(Connection::pointer,
        const std::error_code&);

    asio::io_context& io_context_;
    tcp::acceptor acceptor_;
    bool _debug;
};

class Client : public std::enable_shared_from_this<Client>
{
public:
Client(asio::io_context &context, const std::string &server, int port)
        : _socket(context), _resolver(context), _server(server), _port(port) {}

    void start() {
        resolveServer();
    }

    void write(const std::string &message) {
        asio::post(_socket.get_executor(),
                   [this, message]() {
                       bool write_in_progress = !_write_queue.empty();
                       _write_queue.push_back(message);
                       if (!write_in_progress) {
                           doWrite();
                       }
                   });
    }

    void close() {
        asio::post(_socket.get_executor(), [this]() {
            _socket.close();
        });
    }

private:
    void resolveServer() {
        auto self = shared_from_this();
        _resolver.async_resolve(_server, std::to_string(_port),
            [this, self](std::error_code ec, asio::ip::tcp::resolver::results_type endpoints) {
                if (!ec) {
                    connectToServer(endpoints);
                } else {
                    std::cerr << "Error resolving server: " << ec.message() << std::endl;
                }
            });
    }

    void connectToServer(asio::ip::tcp::resolver::results_type endpoints) {
        auto self = shared_from_this();
        asio::async_connect(_socket, endpoints,
            [this, self](std::error_code ec, asio::ip::tcp::endpoint) {
                if (!ec) {
                    doRead();
                } else {
                    std::cerr << "Error connecting to server: " << ec.message() << std::endl;
                }
            });
    }

    void doRead() {
        auto self = shared_from_this();
        _socket.async_read_some(asio::buffer(_read_buffer),
            [this, self](std::error_code ec, std::size_t length) {
                if (!ec) {
                    std::cout << "Server: " << std::string(_read_buffer.data(), length) << std::endl;
                    doRead();
                } else {
                    std::cerr << "Error reading from server: " << ec.message() << std::endl;
                    _socket.close();
                }
            });
    }

    void doWrite() {
        auto self = shared_from_this();
        asio::async_write(_socket,
            asio::buffer(_write_queue.front()),
            [this, self](std::error_code ec, std::size_t /*length*/) {
                if (!ec) {
                    _write_queue.pop_front();
                    if (!_write_queue.empty()) {
                        doWrite();
                    }
                } else {
                    std::cerr << "Error writing to server: " << ec.message() << std::endl;
                    _socket.close();
                }
            });
    }
private:
    asio::ip::tcp::socket _socket;
    asio::ip::tcp::resolver _resolver;
    std::array<char, 1024> _read_buffer;
    std::deque<std::string> _write_queue;
    std::string _server;
    int _port;
};
    }
  }

#endif  // SERVER_INCLUDE_NETWORKING_LOBBY_HPP_