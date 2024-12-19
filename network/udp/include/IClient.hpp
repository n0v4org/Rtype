/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** IClient
*/

#ifndef NETWORK_UDP_INCLUDE_ICLIENT_HPP_
#define NETWORK_UDP_INCLUDE_ICLIENT_HPP_

#include <array>
#include "Input.hpp"

class IClient {
    public:
      virtual void close_connection() = 0;
      virtual input_t popMessage() = 0;
      virtual bool isQueueEmpty() = 0;
      virtual void send(std::array<uint8_t, 1024> buff) = 0;
      virtual void startReceive() = 0;

    protected:
    private:
};

#endif // NETWORK_UDP_INCLUDE_ICLIENT_HPP_
