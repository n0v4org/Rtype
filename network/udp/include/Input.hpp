/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Input
*/

#ifndef INPUT_HPP_
#define INPUT_HPP_

struct input_t {
    uint8_t cmd;
    uint16_t payload_size;
    uint32_t seq;
    std::array<uint8_t, 1024 > payload;
};


#endif /* !INPUT_HPP_ */
