/*
** EPITECH PROJECT, 2025
** leVraiRtype
** File description:
** Console
*/

#include "Console.hpp"
#include "Engine.hpp"

namespace zef {

Console::Console() {};

Console::~Console() {};
    

void Console::run(std::mutex &mutex, Engine &engine) {
    std::string input("");
    while (1) {
    {
        std::unique_lock<std::mutex> lock(mutex);
        std::cout << "> ";
        std::getline(std::cin, input);
        if (input == "help")
        help();
        else if (engine.GraphLib && input.rfind("playSound ", 0) == 0)
        playSound(engine, input.substr(10));
        else if (input.rfind("debug ", 0) == 0)
        debug(input.substr(6));
        else if (engine.GraphLib && input.rfind("hitbox ", 0) == 0)
        hitbox(engine, input.substr(7));
        else if (engine.GraphLib && input.rfind("metrics ", 0) == 0)
            metrics(engine, input.substr(8));
        else
        std::cout << "Command \"" << input
                    << "\" unknown type \"help\" to display all commands."
                    << std::endl;
    }
    }
}


void Console::help() {
    std::cout << "\thelp               -> Display all commands." << std::endl;
    std::cout << "\tdebug [on | off]   -> Turn on or off debug log."
            << std::endl;
    std::cout << "\tplaySound [name]   -> Play a sound by name." << std::endl;
    std::cout << "\tmetrics [on | off] -> Toggle metrics displaying." << std::endl;
    std::cout << "\thitbox  [on | off] -> Toggle hitboxes displaying." << std::endl;
}

void Console::hitbox(Engine &engine, const std::string &turn) {
    if (turn == "on")
        engine.showHitboxes = true;
    else if (turn == "off")
        engine.showHitboxes = false;
    else
    std::cout << "[HITBOX]: argument \"" << turn
                << "\" unknown, must be \"on\" or \"off\"." << std::endl;
}

void Console::metrics(Engine &engine, const std::string &turn) {
    if (turn == "on")
        engine.showMetrics = true;
    else if (turn == "off")
        engine.showMetrics = false;
    else
    std::cout << "[METRICS]: argument \"" << turn
                << "\" unknown, must be \"on\" or \"off\"." << std::endl;
        
}

void Console::debug(const std::string &turn) {
    if (turn == "on")
    _debug = true;
    else if (turn == "off")
    _debug = false;
    else
    std::cout << "[DEBUG]: argument \"" << turn
                << "\" unknown, must be \"on\" or \"off\"." << std::endl;
}

void Console::playSound(Engine &engine, const std::string &name) {
    std::cout << "playSound: " << name << std::endl;
    engine.GraphLib->playSound(name);
}

Console &Console::displayMessages() {
    while (!_messageQueue.empty() && _debug) {
        std::cout << "[DEBUG] " << _messageQueue.back() << std::endl;
        _messageQueue.pop();
    }
    return *this;
}

Console &Console::sendMessage(const std::string &message) {
    _messageQueue.push(message);
    return *this;
}

} // namespace zef
