/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Core
*/

#include <iostream>
#include <memory>

#include "macro.hpp"
#include "Core.hpp"

Core::Core(char *argv[], int argc)
{
    _args = std::make_unique<Arguments>(argc, argv);
}

void Core::run()
{
    try
    {
        _args->parse();
    }
    catch(const std::exception& e)
    {
        if (strcmp(e.what(), EXCEPTION) != 0)
            std::cerr << e.what() << '\n';
        throw e;
    }
    
}

Core::~Core()
{
}
