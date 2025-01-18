/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** Scene
*/

#ifndef ENGINE_SCENE_HPP_
#define ENGINE_SCENE_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <any>

namespace zef {
  
  class Scene {
  public:
    Scene() = default;

    void setName(const std::string &name) {
      _name = name;
    }

    std::string _name;
    std::vector<std::string> _pat;
    std::vector<std::vector<std::any>> _args;
  };

  class SceneParser {
  public:
    static Scene parse(const std::string &filename) {
      Scene ret;
      nlohmann::json j;
      std::ifstream ifs(filename);
      if (!ifs.is_open()) {
        std::cerr << "error: " << filename << std::endl;
      }
      ifs >> j;
      std::cout << j << std::endl;

      ret.setName(j["name"]);
//    
      int id = 0;
      for (auto &&pat : j["patrons"]) {
        ret._args.emplace_back();
        for (int i = 0; i < pat.size(); i++) {
          if (i != 0) {
            if (pat[i].is_number_float())
            ret._args[id].push_back(static_cast<float>(pat[i]));
            if (pat[i].is_number_integer())
            ret._args[id].push_back(static_cast<int>(pat[i]));
            if (pat[i].is_string()) {
              ret._args[id].push_back(static_cast<std::string>(pat[i]));
            }
          }
        }
        std::cout << ret._args[id].size() << std::endl;
        ret._pat.push_back(pat[0]);
        id++;
      }
      return ret;
    }
  };
}  // namespace zef

#endif  // ENGINE_SCENE_HPP_
