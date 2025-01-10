/*
** EPITECH PROJECT, 2025
** Rtype
** File description:
** Queue
*/

#include <deque>
#include <mutex>
#include <array>
#include "Input.hpp"

extern std::mutex _mutex;

extern std::deque<input_t> tcp_command_queue;
