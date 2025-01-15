/*
** EPITECH PROJECT, 2025
** leVraiRtype
** File description:
** Console
*/

#ifndef CONSOLE_HPP_
#define CONSOLE_HPP_

#include <string>
#include <queue>
#include <map>
#include <iostream>

namespace zef {
  class Console {
  public:
    Console()  = default;
    ~Console() = default;

    Console &displayMessages() {
      while (!_messageQueue.empty()) {
        std::cout << "[INFO] " << _messageQueue.back() << std::endl;
        _messageQueue.pop();
      }
      return *this;
    }

    Console &sendMessage(const std::string &message) {
      _messageQueue.push(message);
      return *this;
    }

  private:
    std::queue<std::string> _messageQueue;
  };

}  // namespace zef

#endif /* !CONSOLE_HPP_ */
