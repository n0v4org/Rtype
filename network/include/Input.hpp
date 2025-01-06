/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Input
*/

#ifndef NETWORK_UDP_INCLUDE_INPUT_HPP_
#define NETWORK_UDP_INCLUDE_INPUT_HPP_

#include <string>

enum {
  TCP_CMD = 0,
  UDP_CMD = 1,
};

struct input_t {
  uint8_t cmd;
  uint16_t payload_size;
  uint32_t seq;
  std::array<uint8_t, 1024> payload;
  std::string tcp_cmd;
  std::string tcp_payload;
  int protocol_type;
  int id;
};


#endif  // NETWORK_UDP_INCLUDE_INPUT_HPP_
