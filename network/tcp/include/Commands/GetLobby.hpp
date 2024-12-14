/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** GetLobby
*/

#ifndef GETLOBBY_HPP_
#define GETLOBBY_HPP_

#include "ACommand.hpp"
#include <nlohmann/json.hpp>

class GetLobby : public ACommand
{
    public:
        GetLobby(json data);
        void exec_cmd(std::string, asio::ip::tcp::socket&) override;
        ~GetLobby();

    protected:
    private:
};

#endif /* !GETLOBBY_HPP_ */
