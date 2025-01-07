/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** positions
*/

#ifndef POSITIONS_HPP_
#define POSITIONS_HPP_

namespace zef {
  namespace comp {
    class position {
    public:
      position(float posX, float posY) : x(posX), y(posY) {
      }
      ~position() = default;

      float x;
      float y;
    };
  }  // namespace comp

}  // namespace zef

#endif /* !POSITIONS_HPP_ */
