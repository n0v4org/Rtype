/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** ACommand
*/

#ifndef ACOMMAND_HPP_
#define ACOMMAND_HPP_

#include <vector>
#include <string>

#include "ICommand.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ACommand : public ICommand
{
    public:
        ACommand(json data)
        : _nb_args(data["params"]["nb_args"].get<int>()), _payload_type(data["params"]["types"].get<std::vector<std::string>>()) {};
        virtual void exec_cmd() override = 0;
        std::string get_resp() const override { return "";}
        int get_nb_args() const { return _nb_args;}
        std::vector<std::string> get_payload() const { return _payload_type;}

    protected:
    private:
        int _nb_args;
        std::vector<std::string> _payload_type;
};

#endif /* !ACOMMAND_HPP_ */
