/*
** EPITECH PROJECT, 2025
** RTYPE
** File description:
** IModule
*/

#ifndef IMODULE_HPP_
#define IMODULE_HPP_

#include <any>
#include <vector>
#include <string>

namespace zef {
  class Engine;
  class IModule {
  public:
    IModule() {
    }
    virtual ~IModule() {
    }

    virtual void registerComponents(Engine& engine)           = 0;
    virtual void registerSystems(Engine& engine)              = 0;
    virtual void emplaceComponent(Engine& engine, size_t e,
                                  const std::string& name,
                                  std::vector<std::any> args) = 0;
    //virtual std::any getMember(const std::string& compname, const std::string& membername) = 0;
  };
}  // namespace zef

#endif /* !IMODULE_HPP_ */
