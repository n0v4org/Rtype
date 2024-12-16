/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Commands
*/

#ifndef NETWORK_UDP_INCLUDE_COMMANDS_HPP_
#define NETWORK_UDP_INCLUDE_COMMANDS_HPP_

#include <algorithm>
#include "Input.hpp"

namespace network {
  namespace game {

    static input_t unpack(std::size_t byte_size,
                          std::array<uint8_t, 1024> _recv_buffer_) {
      input_t input = {0};

      input.cmd          = _recv_buffer_[0];
      input.payload_size = (_recv_buffer_[1] << 8) | _recv_buffer_[2];
      input.seq          = 0;
      for (int i = 0; i < 4; i++) {
        input.seq = (input.seq << 8) | _recv_buffer_[3 + i];
      }
      if (input.payload_size > 1024 || input.payload_size > (byte_size - 7)) {
        throw std::runtime_error("Invalid payload size");
      }
      std::copy(_recv_buffer_.begin() + 7,
                _recv_buffer_.begin() + 7 + input.payload_size,
                input.payload.begin());
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

      static std::array<uint8_t, 1024> toArray(const T& data, input_t& input) {
        std::array<uint8_t, 1024> result = {0};

        constexpr size_t dataSize = sizeof(T);
        if ((dataSize + 7) > result.size()) {
          throw std::runtime_error("Combined data size exceeds array capacity");
        }

        result[0] = input.cmd;
        result[1] = static_cast<uint8_t>(input.payload_size >> 8);
        result[2] = static_cast<uint8_t>(input.payload_size & 0xFF);

        result[3] = static_cast<uint8_t>((input.seq >> 24) & 0xFF);
        result[4] = static_cast<uint8_t>((input.seq >> 16) & 0xFF);
        result[5] = static_cast<uint8_t>((input.seq >> 8) & 0xFF);
        result[6] = static_cast<uint8_t>(input.seq & 0xFF);

        std::memcpy(result.data() + 7, &data, dataSize);
        input.payload_size = dataSize;
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
