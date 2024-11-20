/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Core
*/

#ifndef SERVER_INCLUDE_CORE_HPP_
    #define SERVER_INCLUDE_CORE_HPP_
    #include <memory>
    #include "Arguments.hpp"

class Core {
    public:
        Core(char *[], int);
        void run();
        ~Core();

    protected:
    private:
        std::unique_ptr<Arguments> _args;
};

#endif  // SERVER_INCLUDE_CORE_HPP_
