/*
** EPITECH PROJECT, 2025
** RTYPE
** File description:
** IModule
*/

#ifndef AMODULE_HPP_
#define AMODULE_HPP_

#include <typeindex>
#include <boost/type_index.hpp>
#include "IModule.hpp"
#include "Engine.hpp"

namespace zef {
  

  template <typename Comp, typename ...T>
  class Component {
    public:
      static std::string getType() {
        std::cout << "Pretty Name: " << boost::typeindex::type_id<Comp>().pretty_name() << std::endl;
        return boost::typeindex::type_id<Comp>().pretty_name();
      }


      static void selfRegister(Engine& engine) {
        engine.registerComponent<Comp>();
      }

      static void construct(Engine& engine, size_t e, std::vector<std::any> args) {
        _construct(engine, e, args, std::make_index_sequence<sizeof...(T)>{});
      }

    private:
      template<std::size_t... Indexes>
      static void _construct(Engine& engine, size_t e, std::vector<std::any> args, std::index_sequence<Indexes...>) {
        
        try
        {
          engine.addEntityComponent<Comp>(ecs::Entity(e), std::any_cast<T>(args[Indexes])...);
        }
        catch(const std::exception& e)
        {
          std::cerr << e.what() << '\n';
        }
      }
    };

  template <typename ...Components>
  class AModule : public IModule {
  public:
    AModule() = default;
    virtual ~AModule() = default;

    void registerComponents(Engine& engine) {
      ((Components::selfRegister(engine)), ...);
    }
    
    virtual void registerSystems(Engine& engine) = 0;

    void emplaceComponent(Engine& engine, size_t e, const std::string& name, std::vector<std::any> args)  {
        (([&](){
          if (name == Components::getType()) {
            Components::construct(engine, e, args);
          }
        }()), ...);
    }


    int u;
  };
}  // namespace zef

#endif /* !AMODULE_HPP_ */
