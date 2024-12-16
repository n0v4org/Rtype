/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Input
*/

#ifndef NETWORK_UDP_INCLUDE_INPUT_HPP_
#define NETWORK_UDP_INCLUDE_INPUT_HPP_

struct input_t {
    uint8_t cmd;
    uint16_t payload_size;
    uint32_t seq;
    std::array<uint8_t, 1024 > payload;
};


#endif // NETWORK_UDP_INCLUDE_INPUT_HPP_
