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

#include "ILibHolder.hpp"

namespace zef {
  template <typename T>
  class LibHolder : public ILibHolder<T> {
  public:
    explicit LibHolder(const std::string &filename) {
      
    }
    ~LibHolder() {
      //dlclose(_handle);
    }

    T *getEntryPoint() {
      return nullptr;
    }

  private:
    void *_handle;
  };
};  // namespace zef

#endif /* !WINDOWSLIBHOLDER_HPP_ */
