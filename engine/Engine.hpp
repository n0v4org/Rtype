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
#include <functional>
#include <vector>
#include <filesystem>

#include <iostream>
#include <asio.hpp>

#include "udp/include/Server.hpp"
#include "udp/include/Client.hpp"

#include "graphic/includes/IDisplayModule.hpp"
#include "graphic/includes/ADisplayModule.hpp"

#include "ecs/registry.hpp"
#include "Events.hpp"
#include "utils/inputsUtils.hpp"

#include "IModule.hpp"
#include "LibHolder.hpp"
#include "Patron.hpp"

// #include "Scene.hpp"
// #include "Patron.hpp"

namespace zef {
  namespace sys {
    void resolveEvent(Engine& engine,
                      ecs::sparse_array<comp::event_listener>& evtls);
  }  // namespace sys

  class Engine {
  public:
    Engine() {
      clock = std::chrono::high_resolution_clock::now();
    }
    ecs::registry reg;

    friend void sys::resolveEvent(
        Engine& engine, ecs::sparse_array<comp::event_listener>& evtls);

    template <typename T, typename... U>
    void sendEvent(size_t entity, U... args) {
      Event evt;
      evt.entity = entity;
      T str      = {args...};
      evt.tpl    = str;
      evt.tid    = std::type_index(typeid(T));
      _events.push(evt);
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
    void addEntityComponent(ecs::Entity const& e, const std::string& name, T... args) {
      for (auto &&[n, rtc] : _runtime_modules) {
        rtc->emplaceComponent(*this, e, name, {args...});
      }
    }
    void addEntityComponent(ecs::Entity const& e, const std::string& name, std::vector<std::any> args) {
      for (auto &&[n, rtc] : _runtime_modules) {
        rtc->emplaceComponent(*this, e, name, args);
      }
    }

    template <typename Component>
    void removeEntityComponent(ecs::Entity const& e) {
      reg.remove_component<Component>(e);
    }

    template <class... Components, typename Function>
    void addSystem(Function&& f) {
      reg.add_system<Components...>(f);
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

    ecs::Entity instanciatePatron(const std::string& name, std::vector<std::any> args) {
      ecs::Entity new_entity = reg.spawn_entity();
      for (auto&& p : _patrons) {
        if (p._name == name) {

          std::map<std::string, std::any> ipt;
          int incr = 0;
          for (auto &&[n, t] : p._inputs) {
            ipt[n] = args[incr++];
          }
          
          std::cout << "instanciating :" << name  << std::endl;
          for (auto &&[n, ags] : p._components) {
            std::vector<std::any> pargs;
            for (auto &&ag : ags) {
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
                std::any val = ipt.at(in);
                if (type == "int")
                  pargs.push_back(val);
                if (type == "float")
                  pargs.push_back(val);
                if (type == "str")
                  pargs.push_back(val);
              }
            }
            addEntityComponent(new_entity, n, pargs);

          }
        }
      }
      return new_entity;
    }

    void loadPatron(const std::string& fname) {
      _patrons.push_back(PatronParser::parse(fname));
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

    template <typename T>
    void registerScene(const std::string& name) {
      _scenes[name] = [](Engine& engine) { engine._loadScene<T>(); };
    }

    void run() {
      clock = std::chrono::high_resolution_clock::now();
      int i = 0;
      while (true) {
        elapsed = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now() - clock);
        clock = std::chrono::high_resolution_clock::now();
        //std::cout << i++ << std::endl;

        if (GraphLib)
          GraphLib->clear();

        reg.run_systems(*this);

        if (GraphLib)
          GraphLib->refresh();

        if (_next_scene != "") {
          for (int i = 0; i < reg.getMaxId(); i++) {
            reg.kill_entity(ecs::Entity(i));
          }
          _scenes[_next_scene](*this);
          _next_scene = "";
        }
      }
    }

    void initServer(int port) {
      // network::game::Server s(ctx, 5456);
      _server         = std::make_unique<network::game::Server>(_context, port);
      _network_thread = std::thread([this]() { this->_context.run(); });
    }

    void initClient(int sport, int cport, std::string ip) {
      _client =
          std::make_unique<network::game::Client>(sport, cport, ip, _context);
      _network_thread = std::thread([this]() { this->_context.run(); });
    }

    template <typename cmd>
    void ClientSend(int cmd_id, cmd c) {
      input_t intt;
      intt.cmd          = cmd_id;
      intt.payload_size = sizeof(cmd);
      intt.seq          = seq;
      seq++;
      _client->send(network::game::Commands<cmd>::toArray(c, intt));
    }

    template <typename cmd>
    void ServerSend(int id, int cmd_id, cmd c) {
      input_t intt;
      intt.cmd          = cmd_id;
      intt.payload_size = sizeof(cmd);
      intt.seq          = seq;
      seq++;
      _server->send(id, network::game::Commands<cmd>::toArray(c, intt));
    }

    template <typename cmd>
    void ServerSendToAll(int cmd_id, cmd c) {
    }

    void registerCommand(int cmd, std::function<void(Engine&, input_t)> fn) {
      _cmd_map[cmd] = fn;
    }

    void loadModule(const std::string& name) {
      _runtime_lib_holder.push_back(std::make_unique<LibHolder<IModule>>("module" + name));
      _runtime_modules[name] = std::unique_ptr<IModule>(_runtime_lib_holder.at(_runtime_lib_holder.size() - 1)->getEntryPoint());
      
      _runtime_modules[name]->registerComponents(*this);
      _runtime_modules[name]->registerSystems(*this);

    }

    void loadModules() {
      for (const auto& entry : std::filesystem::directory_iterator("./")) {
        std::string mdname = entry.path().filename().string();
        if (mdname.rfind("libmodule", 0) == 0) {
          std::string str = mdname.substr(9);
          auto f = str.find_last_of('.');
          std::string name = str.substr(0, f);
          loadModule(name);
        } 
      }
    }

    std::map<int, std::function<void(Engine&, input_t)>> _cmd_map;
    std::unique_ptr<network::game::Server> _server;
    std::unique_ptr<network::game::Client> _client;
    int seq = 0;

    size_t replicableId = 34;

    asio::io_context _context;
    std::thread _network_thread;

    std::unique_ptr<zef::graph::IDisplayModule> GraphLib;
    std::chrono::high_resolution_clock::time_point
        clock;  // = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds elapsed;
    size_t _enemyCooldown = 0;

  private:
    int gameFps = 60;

    utils::UserInputs _user_inputs;
    std::queue<Event> _events;

    std::unique_ptr<ILibHolder<zef::graph::IDisplayModule>> _grapLibHolder;

    std::map<std::string, std::function<void(Engine&)>> _scenes;
    std::string _next_scene = "";

    std::vector<std::unique_ptr<zef::ILibHolder<zef::IModule>>> _runtime_lib_holder;
    std::map<std::string, std::unique_ptr<zef::IModule>> _runtime_modules;


    std::vector<Patron> _patrons;
  };

  namespace sys {
    void resolveEvent(Engine& engine,
                      ecs::sparse_array<comp::event_listener>& evtls);
  }
}  // namespace zef

#endif  // ENGINE_ENGINE_HPP_
