/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Core
*/

#ifndef SERVER_INCLUDE_CORE_HPP_
#define SERVER_INCLUDE_CORE_HPP_
#include <memory>
#include <thread>
#include <vector>
#include "Arguments.hpp"
#include "GameServer.hpp"

namespace rtype {

  class Core {
  public:
    Core(char *[], int);
    void run();
    ~Core();

  protected:
  private:
    std::unique_ptr<Arguments> _args;
    std::unique_ptr<GameServer> _server;
    std::vector<std::thread> _games;
    std::thread t;
  };

}  // namespace rtype

#endif  // SERVER_INCLUDE_CORE_HPP_
