/*
** EPITECH PROJECT, 2025
** RTYPE
** File description:
** IModule
*/

#ifndef AMODULE_HPP_
#define AMODULE_HPP_

#include <typeindex>
#include "IModule.hpp"
#include "Engine.hpp"


namespace zef {
  

  //template <typename Comp, typename ...T>
  //class Component {
  //  public:
//
  //    void construct(Engine& engine, size_t e, std::vector<std::any> args) {
  //        engine.addEntityComponent<Components>(ecs::Entity(e), 5, 3.0f,3.0);
  //    }};

  template <typename ...Components>
  class AModule : public IModule {
  public:
    AModule() {
    }
    virtual ~AModule() {
    }

    void registerComponents(Engine& engine) {
      ((engine.registerComponent<Components>()), ...);
    }

    

    virtual void registerSystems(Engine& engine)    = 0;

    void emplaceComponent(Engine& engine, size_t e, const std::string& name, std::vector<std::any> args)  {
        (([&](){
          if (name == std::type_index(typeid(Components)).name()) {
            std::cout << "salam: " << args[0].type().name() << std::endl;
            engine.addEntityComponent<Components>(ecs::Entity(e), 5, 3.0f,3.0);
          }
        }()), ...);
    }


    int u;
  };
}  // namespace zef

#endif /* !AMODULE_HPP_ */
