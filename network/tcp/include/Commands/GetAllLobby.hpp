/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** GetAllLobby
*/

#ifndef GETALLLOBBY_HPP_
#define GETALLLOBBY_HPP_

#include "ACommand.hpp"
#include <nlohmann/json.hpp>

class GetAllLobby : public ACommand
{
    public:
        GetAllLobby(json data);
        void exec_cmd(std::string, asio::ip::tcp::socket&) override;
        ~GetAllLobby();

    protected:
    private:
};

#endif /* !GETALLLOBBY_HPP_ */
