/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_
#include <memory>
#include "Arguments.hpp"

namespace rtype {

class Core {
    public:
        Core(int, char *[]);
        void run();
        ~Core();

    protected:
    private:
        std::unique_ptr<Arguments> _params;
};

} // namespace rtype
 
#endif /* !CORE_HPP_ */
