/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** queue
*/

#include "queue.hpp"

std::mutex _mutex;

std::deque<input_t> tcp_command_queue;
