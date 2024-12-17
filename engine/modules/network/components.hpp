/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** components
*/

#ifndef ENGINE_MODULES_NETWORK_COMPONENTS_HPP_
#define ENGINE_MODULES_NETWORK_COMPONENTS_HPP_

#include "../../Engine.hpp"

namespace zef
{
    namespace comp
    {
        class replicable {
            public:
            explicit replicable(size_t id) {
                _id = id;
            }
            size_t _id;
        };


        

    } // namespace comp
} // namespace zef



#endif // ENGINE_MODULES_NETWORK_COMPONENTS_HPP_
