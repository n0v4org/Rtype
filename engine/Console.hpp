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

#include "Engine.hpp"

namespace zef {
  class Console {
  public:
    Console()  = default;
    ~Console() = default;

    void run(std::mutex &mutex, Engine &engine) {
      std::string input("");
      while (1) {
        {
          std::unique_lock<std::mutex> lock(mutex);
          std::cout << "> ";
          std::getline(std::cin, input);
          if (input == "help")
            help();
          else if (input.rfind("playSound ", 0) == 0)
            playSound(engine, input.substr(10));
          else if (input.rfind("debug ", 0) == 0)
            debug(input.substr(6));
          else
            std::cout << "Command \"" << input
                      << "\" unknown type \"help\" to display all commands."
                      << std::endl;
        }
      }
    }

    void help() {
      std::cout << "\thelp             -> Display all commands." << std::endl;
      std::cout << "\tdebug [on | off] -> Turn on or off debug log."
                << std::endl;
      std::cout << "\tplaySound [name] -> Play a sound by name." << std::endl;
    }

    void debug(const std::string &turn) {
      if (turn == "on")
        _debug = true;
      else if (turn == "off")
        _debug = false;
      else
        std::cout << "[DEBUG]: argument \"" << turn
                  << "\" unknown, must be \"on\" or \"off\"." << std::endl;
    }

    void playSound(Engine &engine, const std::string &name) {
      std::cout << "playSound: " << name << std::endl;
      // engine.GraphLib->playSound("")
    }

    Console &displayMessages() {
      while (!_messageQueue.empty()) {
        if (_debug)
          std::cout << "[DEBUG] " << _messageQueue.back() << std::endl;
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
    bool _debug = false;
  };

}  // namespace zef

#endif /* !CONSOLE_HPP_ */
