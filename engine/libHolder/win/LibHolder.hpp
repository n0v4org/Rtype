/*
** EPITECH PROJECT, 2024
** leVraiRtype
** File description:
** LinuxLibHolder
*/

#ifndef WINDOWSLIBHOLDER_HPP_
#define WINDOWSLIBHOLDER_HPP_

#include <windows.h>
#include <stdexcept>
#include <string>

#include <dylib.hpp>

#include "ILibHolder.hpp"

namespace zef {
  template <typename T>
  class LibHolder : public ILibHolder<T> {
    typedef T *(*EntryPointFunc)();

  public:
    explicit LibHolder(const std::string &filename) : _handler(filename) {
    }
    ~LibHolder() {
    }

    T *getEntryPoint() {
      auto *fn = _handler.get_function<T *()>("entryPoint");
      return fn();
    }

  private:
    dylib _handler;
  };
};  // namespace zef

#endif /* !WINDOWSLIBHOLDER_HPP_ */
