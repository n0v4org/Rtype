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
#include <mutex>


namespace zef {
    class Engine;
  class Console {

  public:
    Console();
    ~Console();

    void run(std::mutex &mutex, Engine &engine);

    void help();

    void debug(const std::string &turn);

    void metrics(Engine &engine, const std::string &turn);

    void hitbox(Engine &engine, const std::string &turn);

    void playSound(Engine &engine, const std::string &name);

    Console &displayMessages();

    Console &sendMessage(const std::string &message);

  private:
    std::queue<std::string> _messageQueue;
    bool _debug = false;
  };

}  // namespace zef

#endif /* !CONSOLE_HPP_ */
