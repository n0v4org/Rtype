/*
** EPITECH PROJECT, 2025
** RTYPE
** File description:
** IModule
*/

#ifndef IMODULE_HPP_
#define IMODULE_HPP_


namespace zef {
    class Engine;
  class IModule {
  public:
    IModule() {
    }
    virtual ~IModule() {
    }

    virtual void registerComponents(Engine& engine) = 0;
    virtual void registerSystems(Engine& engine)    = 0;
  };
}  // namespace zef

#endif /* !IMODULE_HPP_ */
