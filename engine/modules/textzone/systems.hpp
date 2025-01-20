/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** systems
*/

#ifndef ENGINE_MODULES_TEXT_ZONE_SYSTEMS_HPP_
#define ENGINE_MODULES_TEXT_ZONE_SYSTEMS_HPP_

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

#include "../../Engine.hpp"
#include "components.hpp"
#include "../../utils/positions.hpp"
#include "ChatMessagesPatron.hpp"

namespace zef {
  namespace sys {
    inline void UpdateTextInputs(zef::Engine& engine,
                               ecs::sparse_array<comp::textZone>& textZones,
                               ecs::sparse_array<comp::position>& positions) {
      for (auto &k : engine.getUserInputs().keyboard._pressed){
        if (k != 0){
          std::cout << "key presed: "<< k << std::endl;
          for (auto&& [i, txt, pos] : ecs::indexed_zipper(textZones, positions)) {
              if (txt._focused){
                if (k == zef::utils::Backspace && txt._string.size() >= 1)
                   txt._string = txt._string.std::string::substr(0,txt._string.size()-1);
                if (k == zef::utils::Enter) {
                  /**/
                  for (auto &&[a,b,c] : ecs::indexed_zipper(textZones, engine.reg.get_components<MsgZone>())) {
          					if (b._string != ""){
                      std::string q = "SEND_MSG " + b._string;
                      std::cout << q << std::endl;
                      txt._string = "";
                      engine.ClientSendTcp(q);
                    }
                  }
                  for (auto &&[d,e,f] : ecs::indexed_zipper(textZones, engine.reg.get_components<UsrZone>())) {
                    if (e._string != ""){
                      std::string r= "SET_USERNAME " + e._string;
                      std::cout << r << std::endl;
                      txt._string = "";
                      engine.ClientSendTcp(r);
                    }
                  }
                  /**/
                  txt._focused = false;
                }
                if ( k >= 0  && k <= 26 && txt._string.size() <= 16){
                  txt._string += static_cast<char>(k + 65);
                }
              }
          }
        }
      }
    }
    inline void DrawTextInputs(zef::Engine& engine, ecs::sparse_array<comp::textZone>& textZones,
                               ecs::sparse_array<comp::position>& positions) {
      for (auto&& [i, txt, pos] : ecs::indexed_zipper(textZones, positions)) {
        engine.GraphLib->drawText(txt._string, "eth", txt._size, pos.x, pos.y,
                                        1,1,0,{1,1,1,1});
      }
    }
  }  // namespace sys
}  // namespace zef

#endif  // ENGINE_MODULES_TEXT_ZONE_SYSTEMS_HPP_
