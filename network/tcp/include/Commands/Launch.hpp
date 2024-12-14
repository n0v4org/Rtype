/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Launch
*/

#ifndef LAUNCH_HPP_
#define LAUNCH_HPP_

#include "ACommand.hpp"
#include <nlohmann/json.hpp>

class Launch : public ACommand
{
    public:
        Launch(json data);
        void exec_cmd(std::string, asio::ip::tcp::socket&) override;
        ~Launch();

    protected:
    private:
};

#endif /* !LAUNCH_HPP_ */
