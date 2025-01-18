/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** Engine
*/

#ifndef ENGINE_ENGINE_HPP_
#define ENGINE_ENGINE_HPP_

#include <map>
#include <memory>
#include <queue>
#include <thread>
#include <string>
#include <tuple>
#include <functional>
#include <vector>
#include <filesystem>

#include <iostream>
#include <asio.hpp>

#include "include/Network_client.hpp"
#include "include/Network_server.hpp"

#include "graphic/includes/IDisplayModule.hpp"
#include "graphic/includes/ADisplayModule.hpp"

#include "ecs/registry.hpp"
#include "Events.hpp"
#include "utils/inputsUtils.hpp"

#include "IModule.hpp"
#include "LibHolder.hpp"
#include "Patron.hpp"
#include "Scene.hpp"
#include "Console.hpp"

// #include "Scene.hpp"
// #include "Patron.hpp"

namespace zef {
  namespace sys {
    void resolveEvent(Engine& engine,
                      ecs::sparse_array<comp::event_listener>& evtls);

    void nresolveEvent(Engine& engine,
                       ecs::sparse_array<comp::new_event_listener>& evtls);
  }  // namespace sys

  class Engine {
  public:
    Engine() {
      clock = std::chrono::high_resolution_clock::now();
    }
    ecs::registry reg;

    friend void sys::resolveEvent(
        Engine& engine, ecs::sparse_array<comp::event_listener>& evtls);
    friend void sys::nresolveEvent(
        Engine& engine, ecs::sparse_array<comp::new_event_listener>& evtls);

    template <typename T, typename... U>
    void sendEvent(size_t entity, U... args) {
      Event evt;
      evt.entity = entity;
      T str      = {args...};
      evt.tpl    = str;
      evt.tid    = std::type_index(typeid(T));
      _events.push(evt);
    }

    template <typename... U>
    void nsendEvent(std::string name, size_t entity, U... args) {
      newEvent evt;
      evt.name   = name;
      evt.entity = entity;
      evt.tpl    = std::tuple<U...>(args...);

      _nevents.push(evt);
    }

    void resolveEvent() {
      while (!_events.empty()) {
        Event evt = _events.front();
        if (reg.get_components<comp::event_listener>().size() > evt.entity &&
            reg.get_entity_component<comp::event_listener>(
                evt.entity)) {  // handle error when the entity dont handle the
                                // event
          if (reg.get_entity_component<comp::event_listener>(evt.entity)
                  ->_functions.find(evt.tid) !=
              reg.get_entity_component<comp::event_listener>(evt.entity)
                  ->_functions.end())
            reg.get_entity_component<comp::event_listener>(evt.entity)
                ->_functions[evt.tid](*this, evt.entity, evt);
        }
        _events.pop();
      }
    }

    template <typename Component>
    Component& fetchEntityComponent(size_t e) {
      std::optional<Component>& optComp = reg.get_components<Component>()[e];
      if (optComp == std::nullopt)
        throw std::runtime_error("this entity does not have the component");
      return optComp.value();
    }

    template <typename T>
    T& fetchEntityComponentAccessMember(const std::string& comp,
                                        const std::string& membername) {
    }

    template <typename Component>
    void registerComponent() {
      reg.register_component<Component>();
      // reg.get_components<Component>().emplace_component(std::nullopt);
    }

    template <typename Component>
    void addEntityComponent(ecs::Entity e, Component&& c) {
      reg.add_component<Component>(e, c);
    }

    template <typename Component>
    void addEntityComponent(ecs::Entity const& e, Component const& c) {
      reg.add_component<Component>(e, c);
    }

    template <typename Component, typename... T>
    void addEntityComponent(ecs::Entity const& e, T... args) {
      reg.emplace_component<Component>(e, args...);
    }

    template <typename... T>
    void addEntityComponent(ecs::Entity const& e, const std::string& name,
                            T... args) {
      for (auto&& [n, rtc] : _runtime_modules) {
        rtc->emplaceComponent(*this, e, name, {args...});
      }
    }
    void addEntityComponent(ecs::Entity const& e, const std::string& name,
                            std::vector<std::any> args) {
      for (auto&& [n, rtc] : _runtime_modules) {
        rtc->emplaceComponent(*this, e, name, args);
      }
    }

    template <typename Component>
    void removeEntityComponent(ecs::Entity const& e) {
      reg.remove_component<Component>(e);
    }

    template <class... Components, typename Function>
    void addSystem(const std::string& moduleName, Function&& f) {
      reg.add_system<Components...>(*this, moduleName, f);
    }

    template <typename Patron, typename... T>
    ecs::Entity instanciatePatron(T... args) {
      ecs::Entity new_entity = reg.spawn_entity();
      Patron::instanciate(*this, new_entity, args...);
      return new_entity;
    }
    template <typename... T>
    ecs::Entity instanciatePatron(const std::string& name, T... args) {
      return instanciatePatron(name, {args...});
    }

    ecs::Entity instanciatePatron(const std::string& name,
                                  std::vector<std::any> args) {
      ecs::Entity new_entity = reg.spawn_entity();
      std::cout << "nentity: " << new_entity << std::endl;
      for (auto&& p : _patrons) {
        if (p._name == name) {
          std::map<std::string, std::any> ipt;
          int incr = 0;
          for (auto&& [n, t] : p.__inputs) {
            ipt[n] = args[incr++];
          }

          std::cout << "instanciating :" << name << std::endl;
          for (auto&& [n, ags] : p._components) {
            std::vector<std::any> pargs;
            for (auto&& ag : ags) {
              if (ag.is_number_float()) {
                pargs.push_back(ag.get<float>());
              } else if (ag.is_number()) {
                pargs.push_back(ag.get<int>());
              } else if (ag.is_string()) {
                pargs.push_back(ag.get<std::string>());
              } else if (ag.is_object()) {
                std::string in = ag["input"];
                std::cout << in << std::endl;
                std::string type = p._inputs.at(in);
                std::any val     = ipt.at(in);
                if (type == "int")
                  pargs.push_back(val);
                if (type == "float")
                  pargs.push_back(val);
                if (type == "str")
                  pargs.push_back(val);
              }
            }
            if (n == "SCRIPT")
              addEntityComponent<comp::new_event_listener>(new_entity, _script_map[std::any_cast<std::string>(pargs[0])]);
            else
            addEntityComponent(new_entity, n, pargs);
          }
        }
      }
      return new_entity;
    }

    void loadPatron(const std::string& fname) {
      _patrons.push_back(PatronParser::parse(fname));
    }

    void registerScene(const std::string& fname) {
      _scenes_config.push_back(SceneParser::parse(fname));
    }

    void loadSceneConfig(const std::string& name) {
      std::cout << "loading " << name << std::endl;
      for (auto &&s : _scenes_config) {
        if (s._name == name) {
            _new_next_scene = [s](zef::Engine& engine) {
              std::cout << "maxid " << engine.reg._maxId << std::endl;
              for (int i = 0; i < engine.reg.getMaxId(); i++)
                engine.reg.kill_entity(ecs::Entity(i));
              engine.reg._maxId = 0;
              engine.reg._entityCount = 0;

              while (!engine.reg._unusedids.empty()) engine.reg._unusedids.pop();
              
              for (int i = 0; i < s._pat.size(); i++) {
                engine.instanciatePatron(s._pat[i], s._args[i]);
              }
            };
        }
      }
    }

    template <typename Scene>
    void loadScene() {
      Scene::loadScene(*this);
    }

    template <typename Scene>
    void registerScene() {
    }

    void updateUserInputs() {
      _user_inputs.keyboard._released.clear();
      _user_inputs.keyboard._pressed.clear();
      _user_inputs.mouse._pressed.clear();
      _user_inputs.mouse._released.clear();
      GraphLib->updateUserInputs(_user_inputs);
    }

    const utils::UserInputs& getUserInputs() {
      return _user_inputs;
    }

    void initGraphLib(const std::string& assetFolder,
                      const std::string& windowName) {
      _grapLibHolder =
          std::make_unique<LibHolder<zef::graph::IDisplayModule>>("sfml");
      GraphLib.reset(_grapLibHolder->getEntryPoint());
      GraphLib->initialize(assetFolder, "R-type");
    }

    void loadScene(const std::string& name) {
      _next_scene = name;
    }

    template <typename T>
    void _loadScene() {
      T::loadScene(*this);
    }

    template <typename T, typename ...Args>
    void newLoadScene(Args ...args)  {
      _new_next_scene = [&](Engine& engine) {
        for (int i = 0; i < reg.getMaxId(); i++)
            reg.kill_entity(ecs::Entity(i));
        T::loadScene(*this, args...);
      };
    }


    template <typename T>
    void registerScene(const std::string& name) {
      _scenes[name] = [](Engine& engine) { engine._loadScene<T>(); };
    }

    void stop() {
      running = false;
    }

    void run() {
      clock = std::chrono::high_resolution_clock::now();
      int i = 0;
      // ecs::Entity e(reg.spawn_entity());
      // addEntityComponent(e, "ExampleComp1", 2, 2.0f);
      // addEntityComponent(e, "ExampleComp2", 3.0f, 'c');
      std::thread consoleThread([this](){
        console.run(consoleMutex, *this);
      });
      while (running) {
        elapsed = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now() - clock);
        clock = std::chrono::high_resolution_clock::now();

        if (GraphLib)
          GraphLib->clear();

        reg.run_systems(*this);
        console.displayMessages();

        if (GraphLib)
          GraphLib->refresh();

        _new_next_scene(*this);
        _new_next_scene = [](zef::Engine& e) {};

        if (_next_scene != "") {
          for (int i = 0; i < reg.getMaxId(); i++) {
            reg.kill_entity(ecs::Entity(i));
          }
          _scenes[_next_scene](*this);
          _next_scene = "";
        }
      }
      consoleThread.detach();
    }

    void consoleSendMessage(const std::string& message) {
      console.sendMessage(message);
    }

    void initServer(int udpport, int tcpport) {
      _server = std::make_unique<network::Network_server>(udpport, tcpport);
    }
    //
    void initClient(int tcpport, int clientport, int udpport, std::string ip) {
      _client = std::make_unique<network::Network_client>(udpport, clientport,
                                                          tcpport, ip);
    }

    template <typename payload>
    void ClientSendUdp(int cmd_id, payload c) {
      _client->get_udp_client()->send(c, cmd_id);
    }

    void ClientSendTcp(const std::string& c) {
      _client->get_tcp_client()->send(c);
    }

    template <typename payload>
    void ServerSendUdp(int id, int cmd_id, payload c) {
      _server->get_udp_server()->send(id, cmd_id, c);
    }

    void ServerSendTcp(int id, std::string c) {
      _server->get_tcp_server()->send(id, c);
    }
    template <typename payload>
    void ServerSendToAllUdp(int cmd_id, payload c) {
      //_server->get_udp_server()->send(id, cmd_id, c);
    }

    void ServerSendToAllTcp(int cmd_id, std::string c) {
      //_server->get_tcp_server()->send(id, c);
    }

    void ServerSendToAllTcp(std::string c) {
      _server->get_tcp_server()->send_all(c);
    }

    void registerCommand(int cmd, std::function<void(Engine&, input_t)> fn) {
      _cmd_map[cmd] = fn;
    }

    void registerCommandTcp(std::string cmd,
                            std::function<void(Engine&, input_t)> fn) {
      _cmd_map_tcp[cmd] = fn;
    }

    

    void loadModule(const std::string& name) {
      _runtime_lib_holder.push_back(
          std::make_unique<LibHolder<IModule>>("module" + name));
      _runtime_modules[name] = std::unique_ptr<IModule>(
          _runtime_lib_holder.at(_runtime_lib_holder.size() - 1)
              ->getEntryPoint());

      _runtime_modules[name]->registerComponents(*this);

      _runtime_modules[name]->registerSystems(*this);
    }

    void loadModules() {
      for (const auto& entry : std::filesystem::directory_iterator("./")) {
        std::string mdname = entry.path().filename().string();
        if (mdname.rfind("libmodule", 0) == 0) {
          std::string str  = mdname.substr(9);
          auto f           = str.find_last_of('.');
          std::string name = str.substr(0, f);
          loadModule(name);
        }
        if (mdname.rfind("module", 0) == 0) {
          std::string str  = mdname.substr(6);;
          auto f           = str.find_last_of('.');
          std::string name = str.substr(0, f);
          loadModule(name);
        }
      }
    }

    std::map<int, std::function<void(Engine&, input_t)>> _cmd_map;
    std::map<std::string, std::function<void(Engine&, input_t)>> _cmd_map_tcp;
    std::unique_ptr<network::Network_server> _server;
    std::unique_ptr<network::Network_client> _client;
    int seq = 0;

    size_t replicableId = 34;

    std::unique_ptr<zef::graph::IDisplayModule> GraphLib;
    std::chrono::high_resolution_clock::time_point
        clock;  // = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds elapsed;
    size_t _enemyCooldown = 0;
    Console console;
    std::mutex consoleMutex;

    std::map<std::string, std::unique_ptr<zef::IModule>> _runtime_modules;
    std::map<std::string, zef::comp::new_event_listener> _script_map;
  private:
    int gameFps = 60;

    bool running = true;

    utils::UserInputs _user_inputs;
    std::queue<Event> _events;
    std::queue<newEvent> _nevents;

    std::unique_ptr<ILibHolder<zef::graph::IDisplayModule>> _grapLibHolder;

    std::map<std::string, std::function<void(Engine&)>> _scenes;
    std::string _next_scene = "";

    std::function<void(Engine&)> _new_next_scene = [](zef::Engine& e) {};

    std::vector<std::unique_ptr<zef::ILibHolder<zef::IModule>>>
        _runtime_lib_holder;

    std::vector<Patron> _patrons;
    std::vector<Scene> _scenes_config;
  };

  namespace sys {
    void resolveEvent(Engine& engine,
                      ecs::sparse_array<comp::event_listener>& evtls);
  }
}  // namespace zef

#endif  // ENGINE_ENGINE_HPP_
