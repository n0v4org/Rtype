/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** Patron
*/

#ifndef ENGINE_PATRON_HPP_
#define ENGINE_PATRON_HPP_

#include <map>
#include <functional>
#include <istream>
#include <string>
#include <iostream>

#include <nlohmann/json.hpp>

  
namespace zef {

  class Patron {
  public:
    Patron() = default;

    void setName(const std::string &name) {
      _name = name;
    }

    std::string _name;
    std::map<std::string, nlohmann::json> _components;
    std::map<std::string, std::string> _inputs;
    std::vector<std::pair<std::string, std::string>> __inputs;
    std::string _script_name = "";
  };


  class PatronParser {
  public:
    static Patron parse(const std::string &filename) {
      Patron ret;
      nlohmann::json j;
      std::ifstream ifs(filename);
      if (!ifs.is_open()) {
        std::cerr << "error: " << filename << std::endl;
      }
      ifs >> j;
      std::cout << j << std::endl;

      ret.setName(j["name"]);
      //ret._script_name = j["SCRIPT"];

      for (auto &&comp : j["components"]) {
        ret._components[comp["name"]] = comp["args"];
      }
      for (auto &&i : j["inputs"]) {
        ret._inputs[i["name"]] = i["type"];
        ret.__inputs.push_back({i["name"], i["type"]});
        std::cout << "ambiance: " << i << std::endl;
      }

      return ret;
    }
  };
}  // namespace zef

#endif  // ENGINE_PATRON_HPP_
