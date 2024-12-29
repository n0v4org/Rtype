/*
** EPITECH PROJECT, 2024
** leVraiRtype
** File description:
** ILibLoader
*/

#ifndef ENGINE_LIBHOLDER_ILIBHOLDER_HPP_
#define ENGINE_LIBHOLDER_ILIBHOLDER_HPP_

#include <functional>
#include <memory>
#include <string>

namespace zef {
    template<typename T>
    class ILibHolder {
        public:
            virtual ~ILibHolder() = default;
            virtual T* getEntryPoint() = 0;
    };
} // namespace zef

#endif /* !ENGINE_LIBHOLDER_ILIBHOLDER_HPP_ */
