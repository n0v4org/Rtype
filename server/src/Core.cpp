/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Core
*/

#include <iostream>
#include <memory>
#include <cstring>

#include "macro.hpp"
#include "Core.hpp"

static const char USAGE[133] = 
"usage:\n\
\t\t -h: run server in help mod\n\
\t\t -v run server in verbose mode\n\
\t\t -p <port>: run server on specified port (default is 50000)\n";


Core::Core(char *argv[], int argc)
{
    _args = std::make_unique<Arguments>(argc, argv);
}

void Core::run()
{
    try
    {
        _args->parse();
        if (_args->get_help()) {
            std::cout << USAGE << std::endl;
            return;
        }
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
