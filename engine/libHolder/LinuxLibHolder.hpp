/*
** EPITECH PROJECT, 2024
** leVraiRtype
** File description:
** LinuxLibHolder
*/

#ifndef LINUXLIBHOLDER_HPP_
#define LINUXLIBHOLDER_HPP_

#include <dlfcn.h>
#include <stdexcept>
#include <string>

#include "ILibHolder.hpp"

namespace zef {
  template <typename T>
  class LinuxLibHolder : public ILibHolder<T> {
  public:
    explicit LinuxLibHolder(const std::string &filename) {
      _handle = dlopen(("./lib" + filename + ".so").c_str(), RTLD_LAZY);
      if (!_handle) {
        throw std::runtime_error("Error while opening lib: " + filename + ": " +
                                 std::string(dlerror()));
      }
    }
    ~LinuxLibHolder() {
      dlclose(_handle);
    }

    T *getEntryPoint() {
      void *sym = dlsym(_handle, "entryPoint");

      const char *error = dlerror();
      if (error) {
        dlclose(_handle);
        throw std::runtime_error("Error while getting entryPoint: ");
      }

      auto fun = reinterpret_cast<T *(*)()>(sym);
      return fun();
    }

  private:
    void *_handle;
  };
};  // namespace zef

#endif /* !LINUXLIBHOLDER_HPP_ */
