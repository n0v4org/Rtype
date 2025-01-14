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
  class LibHolder : public ILibHolder<T> {
  public:
    explicit LibHolder(const std::string &filename) {
#ifdef __APPLE__
      _handle = dlopen(("./bin/lib" + filename + ".dylib").c_str(), RTLD_LAZY);
#else
      _handle = dlopen(("./lib" + filename + ".so").c_str(), RTLD_LAZY);
#endif
      if (!_handle) {
        throw std::runtime_error("Error while opening lib: " + filename + ": " +
                                 std::string(dlerror()));
      }
    }
    ~LibHolder() {
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
