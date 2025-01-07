/*
** EPITECH PROJECT, 2025
** RTYPE
** File description:
** IModule
*/

#ifndef AMODULE_HPP_
#define AMODULE_HPP_

#include <typeindex>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <functional>

#include "IModule.hpp"
#include "Engine.hpp"

#ifdef __GNUG__
#include <cxxabi.h>

std::string demangle(const char* mangled_name) {
  int status = 0;
  std::unique_ptr<char, void (*)(void*)> demangled(
      abi::__cxa_demangle(mangled_name, nullptr, nullptr, &status), std::free);
  return (status == 0) ? demangled.get() : mangled_name;
}
#else

std::string demangle(const char* name) {
  return name;
}
#endif

namespace zef {

  template <typename Comp, typename... T>
  class Component {
  public:
    static std::string getType() {
      std::cout << "Pretty Name: " << demangle(typeid(Comp).name())
                << std::endl;
      return demangle(typeid(Comp).name());
    }

    static void selfRegister(Engine& engine) {
      engine.registerComponent<Comp>();
    }

    static void construct(Engine& engine, size_t e,
                          std::vector<std::any> args) {
      _construct(engine, e, args, std::make_index_sequence<sizeof...(T)>{});
    }

  private:
    template <std::size_t... Indexes>
    static void _construct(Engine& engine, size_t e, std::vector<std::any> args,
                           std::index_sequence<Indexes...>) {
      try {
        engine.addEntityComponent<Comp>(ecs::Entity(e),
                                        std::any_cast<T>(args[Indexes])...);
      } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
      }
    }
  };

  template <typename... Components>
  class AModule : public IModule {
  public:
    AModule()  = default;
    ~AModule() = default;

    void registerComponents(Engine& engine) {
      ((Components::selfRegister(engine)), ...);
    }

    virtual void registerSystems(Engine& engine) = 0;

    void emplaceComponent(Engine& engine, size_t e, const std::string& name,
                          std::vector<std::any> args) {
      (([&]() {
         if (name == Components::getType()) {
           Components::construct(engine, e, args);
         }
       }()),
       ...);
    }

  };
}  // namespace zef

#endif /* !AMODULE_HPP_ */
