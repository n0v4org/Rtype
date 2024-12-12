/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Join
*/

#ifndef JOIN_HPP_
#define JOIN_HPP_

#include "ACommand.hpp"
#include <nlohmann/json.hpp>

class Join : public ACommand
{
    public:
        Join(json data);

        void exec_cmd() override;

        ~Join();

    protected:
    private:
};

#endif /* !JOIN_HPP_ */
