/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** ICommand
*/

#ifndef ICOMMAND_HPP_
#define ICOMMAND_HPP_

#include <string>

class ICommand {
    public:
        virtual void exec_cmd() = 0;
        virtual std::string get_resp() const = 0;
        virtual ~ICommand() = default;
    protected:
    private:
};

#endif /* !ICOMMAND_HPP_ */
