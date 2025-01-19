/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Commands
*/

#ifndef NETWORK_UDP_INCLUDE_COMMANDS_HPP_
#define NETWORK_UDP_INCLUDE_COMMANDS_HPP_

#include <algorithm>
#include <vector> 
#include <cstring>
#include <iostream>

#include "Input.hpp"
#include <lz4.h>

namespace network {
  namespace game {

    static std::vector<uint8_t> compressVector(const std::vector<uint8_t>& input) {
    int maxCompressedSize = LZ4_compressBound(input.size());
    std::vector<uint8_t> compressedData(maxCompressedSize);

    int compressedSize = LZ4_compress_default(
        reinterpret_cast<const char*>(input.data()),
        reinterpret_cast<char*>(compressedData.data()),
        input.size(),
        maxCompressedSize
    );

    if (compressedSize <= 0) {
        throw std::runtime_error("Compression failed!");
    }

    compressedData.resize(compressedSize);

    return compressedData;
}

static std::vector<uint8_t> decompressVector(const std::vector<uint8_t>& compressed, int originalSize) {
    std::vector<uint8_t> decompressedData(originalSize);

    int decompressedSize = LZ4_decompress_safe(
        reinterpret_cast<const char*>(compressed.data()),
        reinterpret_cast<char*>(decompressedData.data()),
        compressed.size(),
        originalSize
    );

    if (decompressedSize < 0) {
        throw std::runtime_error("Decompression failed!");
    }

    decompressedData.resize(decompressedSize);

    return decompressedData;
}


static input_t unpack(std::size_t byte_size, const std::array<uint8_t, 1024>& _recv_buffer_) {
    input_t input = {};

    if (byte_size < 4) {
        throw std::runtime_error("Invalid data: Header too small");
    }

    uint32_t original_size =
        (_recv_buffer_[0] << 24) | (_recv_buffer_[1] << 16) |
        (_recv_buffer_[2] << 8) | _recv_buffer_[3];

    if (byte_size <= 4) {
        throw std::runtime_error("Invalid data: No compressed payload");
    }
    std::vector<uint8_t> compressed_data(
        _recv_buffer_.begin() + 4,
        _recv_buffer_.begin() + byte_size
    );
    std::cout << compressed_data.size() << std::endl;
    std::vector<uint8_t> decompressed_data = decompressVector(compressed_data, original_size);
    if (decompressed_data.size() < 11) {
        throw std::runtime_error("Invalid decompressed data: Too small");
    }

    input.cmd = decompressed_data[0];
    input.payload_size = (decompressed_data[1] << 8) | decompressed_data[2];
    input.seq = 0;

    for (int i = 0; i < 4; i++) {
        input.seq = (input.seq << 8) | decompressed_data[3 + i];
    }

    if (input.payload_size > 1024 || input.payload_size > (decompressed_data.size() - 7)) {
        throw std::runtime_error("Invalid payload size");
    }

    std::copy(
        decompressed_data.begin() + 7,
        decompressed_data.begin() + 7 + input.payload_size,
        input.payload.begin()
    );

    input.protocol_type = UDP_CMD;
    return input;
}

    template <typename T>
    class Commands {
    public:
      T getCommand() const {
        return _cmd;
      }
      explicit Commands(const input_t& input) {
        parsePayload(input);
      }
      Commands() = default;

      static std::array<uint8_t, 1024> toArray(const T& data, int cmd,
                                               uint32_t seq) {
        std::array<uint8_t, 1024> result = {};

        constexpr size_t dataSize = sizeof(T);
        if ((dataSize + 7) > result.size()) {
          throw std::runtime_error("Combined data size exceeds array capacity");
        }
        std::cout << "cmf" << cmd << std::endl;
        result[0] = cmd;
        std::cout << dataSize << std::endl;
        result[1] = static_cast<uint8_t>(dataSize >> 8);
        result[2] = static_cast<uint8_t>(dataSize & 0xFF);

        result[3] = static_cast<uint8_t>((seq >> 24) & 0xFF);
        result[4] = static_cast<uint8_t>((seq >> 16) & 0xFF);
        result[5] = static_cast<uint8_t>((seq >> 8) & 0xFF);
        result[6] = static_cast<uint8_t>(seq & 0xFF);

        std::memcpy(result.data() + 7, &data, dataSize);
        return result;
      }

      ~Commands() {
      }

    protected:
    private:
      T _cmd;
      void parsePayload(const input_t& input) {
        constexpr size_t dataSize = sizeof(T);

        if (input.payload_size != dataSize) {
          throw std::runtime_error(
              "Payload size does not match expected structure size");
        }
        std::memcpy(&_cmd, input.payload.data(), dataSize);
      }
    };

  }  // namespace game
}  // namespace network

#endif  // NETWORK_UDP_INCLUDE_COMMANDS_HPP_
