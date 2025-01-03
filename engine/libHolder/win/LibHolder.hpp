/*
** EPITECH PROJECT, 2024
** leVraiRtype
** File description:
** LinuxLibHolder
*/

#ifndef WINDOWSLIBHOLDER_HPP_
#define WINDOWSLIBHOLDER_HPP_

#include <stdexcept>
#include <string>
#include <windows.h>

#include "ILibHolder.hpp"

namespace zef {
  template <typename T>
  class LibHolder : public ILibHolder<T> {
  public:
    explicit LibHolder(const std::string &filename) {
      _handle = LoadLibrary(("./lib" + filename + ".dll").c_str())

      if (!_handle) {
          throw std::runtime_error("Error while opening lib: " + filename);
      }
    }
    ~LibHolder() {
      FreeLibrary(_handle);
    }

    T *getEntryPoint() {
        auto fun = reinterpret_cast<T*(*)()>(GetProcAddress(_handle, "entryPoint"));
        return fun();
    }

  private:
    HINSTANCE _handle;
  };
};  // namespace zef

#endif /* !WINDOWSLIBHOLDER_HPP_ */
