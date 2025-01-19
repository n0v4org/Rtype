#ifndef NETWORK_TCP_INCLUDE_CONNECTION_HPP_
#define NETWORK_TCP_INCLUDE_CONNECTION_HPP_

#include <lz4.h>
#include <string>
#include <memory>
#include <mutex>
#include <deque>
#include <vector>
#include <iostream>
#include <asio.hpp>
#include "Input.hpp"
#include "queue.hpp"

using asio::ip::tcp;

static const char CMD_NOT_FOUND[] = "500 cmd not found";

namespace network {
  namespace tcp_link {

    class Connection : public std::enable_shared_from_this<Connection> {
    public:
      using pointer = std::shared_ptr<Connection>;

      static pointer create(asio::io_context& io_context,
                            std::deque<input_t>& queue,
                            std::mutex& queue_mutex) {
        return pointer(new Connection(io_context, queue, queue_mutex));
      }

      tcp::socket& socket() {
        return socket_;
      }

      void write(const std::string& msg) {
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

      void start() {
        do_read_header();
      }

      void assign_id(int id) {
        _id = id;
      }

    private:
      Connection(asio::io_context& io_context, std::deque<input_t>& queue,
                 std::mutex& queue_mutex)
        : socket_(io_context), queue_(queue), queue_mutex_(queue_mutex) {
      }

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
          message.id           = _id;
          message.payload      = {};

          message.tcp_cmd       = cmd;
          message.tcp_payload   = payload;
          message.protocol_type = TCP_CMD;

          {
            std::lock_guard<std::mutex> lock(queue_mutex_);
            queue_.push_back(message);
          }
        } catch (const std::exception& e) {
          std::cerr << "Error processing message: " << e.what() << "\n";
          write(CMD_NOT_FOUND);
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

      tcp::socket socket_;
      char header_[8];
      std::vector<char> read_buffer_;
      std::deque<input_t>& queue_;
      std::mutex& queue_mutex_;
      int _id = 0;
    };
  }  // namespace tcp_link
}  // namespace network

#endif  // NETWORK_TCP_INCLUDE_CONNECTION_HPP_