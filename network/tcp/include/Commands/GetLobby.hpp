/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** GetLobby
*/

#ifndef NETWORK_TCP_INCLUDE_COMMANDS_GETLOBBY_HPP_ 
#define NETWORK_TCP_INCLUDE_COMMANDS_GETLOBBY_HPP_ 

#include <string>

#include "ACommand.hpp"
#include <nlohmann/json.hpp>

class GetLobby : public ACommand
{
    public:
        explicit GetLobby(json data);
        void exec_cmd(std::string, asio::ip::tcp::socket&) override;
        ~GetLobby();

    protected:
    private:
};

#endif // NETWORK_TCP_INCLUDE_COMMANDS_GETLOBBY_HPP_ 
