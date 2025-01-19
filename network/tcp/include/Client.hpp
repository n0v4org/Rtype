#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <lz4.h>
#include <iostream>
#include <mutex>
#include <deque>
#include <string>
#include <vector>
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
        if (socket_.is_open()) {
          socket_.cancel();
          socket_.close();
        }
      }

      ~Client();

      void connect(const std::string& host, const int port) {
        asio::ip::tcp::resolver resolver(io_context_);
        std::cout << "Connecting to " << host << ":" << port << std::endl;
        auto endpoints = resolver.resolve(host, std::to_string(port));

        asio::async_connect(
            socket_, endpoints,
            [this](std::error_code ec, const asio::ip::tcp::endpoint&) {
              if (!ec) {
                std::cout << "Connected to server.\n";
                do_read_header();
              } else {
                std::cerr << "Connection failed: " << ec.message() << "\n";
              }
            });
      }

      void send(const std::string& msg) {
        std::string compressed_data = compressString(msg);

        uint32_t compressed_size = compressed_data.size();
        uint32_t original_size   = msg.size();
        char header[8];
        std::memcpy(header, &compressed_size, 4);
        std::memcpy(header + 4, &original_size, 4);

        std::string framed_data(header, sizeof(header));
        framed_data += compressed_data;

        asio::async_write(socket_, asio::buffer(framed_data),
                          [this](std::error_code ec, std::size_t /*length*/) {
                            if (ec) {
                              std::cerr << "Write error: " << ec.message()
                                        << "\n";
                            }
                          });
      }

    private:
      void do_read_header() {
        asio::async_read(socket_, asio::buffer(header_, 8),
                         [this](std::error_code ec, std::size_t /*length*/) {
                           if (!ec) {
                             uint32_t compressed_size = 0, original_size = 0;
                             std::memcpy(&compressed_size, header_, 4);
                             std::memcpy(&original_size, header_ + 4, 4);
                             do_read_body(compressed_size, original_size);
                           } else {
                             std::cerr << "Header read error: " << ec.message()
                                       << "\n";
                           }
                         });
      }

      void do_read_body(uint32_t compressed_size, uint32_t original_size) {
        read_buffer_.resize(compressed_size);
        asio::async_read(socket_, asio::buffer(read_buffer_),
                         [this, original_size, compressed_size](
                             std::error_code ec, std::size_t /*length*/) {
                           if (!ec) {
                             std::cout << "compressed size: " << compressed_size
                                       << std::endl;
                             process_message(read_buffer_, original_size);
                             do_read_header();
                           } else {
                             std::cerr << "Body read error: " << ec.message()
                                       << "\n";
                           }
                         });
      }

      void process_message(const std::vector<char>& compressed_data,
                           uint32_t original_size) {
        try {
          std::string input = decompressString(compressed_data, original_size);
          std::cout << "decommpres size: " << input.size() << std::endl;
          std::cout << "input " << input << std::endl;
          std::size_t cmd_len = input.find(' ');
          std::string cmd =
              (cmd_len != std::string::npos) ? input.substr(0, cmd_len) : input;
          std::string payload =
              (cmd_len != std::string::npos) ? input.substr(cmd_len + 1) : "";

          trim(cmd);
          trim(payload);

          input_t message      = {};
          message.cmd          = 0;
          message.payload_size = payload.size();
          message.seq          = 0;
          message.id           = 0;
          message.payload      = {};

          message.tcp_cmd       = cmd;
          message.tcp_payload   = payload;
          message.protocol_type = TCP_CMD;

          {
            std::lock_guard<std::mutex> lock(_mutex);
            _command_queue.push_back(message);
          }
        } catch (const std::exception& e) {
          std::cerr << "Error processing message: " << e.what() << "\n";
        }
      }

      std::string compressString(const std::string& input) {
        int maxCompressedSize = LZ4_compressBound(input.size());
        std::vector<char> compressedData(maxCompressedSize);

        int compressedSize =
            LZ4_compress_default(input.c_str(), compressedData.data(),
                                 input.size(), maxCompressedSize);

        if (compressedSize <= 0) {
          throw std::runtime_error("Compression failed!");
        }

        return std::string(compressedData.data(), compressedSize);
      }

      std::string decompressString(const std::vector<char>& compressed,
                                   uint32_t original_size) {
        std::vector<char> decompressedData(original_size);

        int decompressedSize =
            LZ4_decompress_safe(compressed.data(), decompressedData.data(),
                                compressed.size(), original_size);

        if (decompressedSize < 0) {
          throw std::runtime_error("Decompression failed with error code: " +
                                   std::to_string(decompressedSize));
        }

        return std::string(decompressedData.data(), decompressedSize);
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

      asio::io_context& io_context_;
      asio::ip::tcp::socket socket_;
      char header_[8];
      std::vector<char> read_buffer_;
      std::deque<input_t> _command_queue;
      std::mutex _mutex;
    };

  }  // namespace tcp_link
}  // namespace network

#endif /* !CLIENT_HPP_ */