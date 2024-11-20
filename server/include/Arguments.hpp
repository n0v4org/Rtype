/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Arguments
*/

#ifndef ARGUMENTS_HPP_
    #define ARGUMENTS_HPP_
    #include <string>
    #include <vector>
    #include <map>

static const std::vector<std::string> FLAGS = {
    "-p",
    "-h",
    "-v",
};

enum {
    PORT = 0,
    HELP = 1,
    DEBUG = 2,
};

class Arguments {
    public:
        Arguments(int, char *[]);
        bool is_number (std::string);
        void parse();
        int get_port() const;
        bool get_help() const;
        bool get_debug() const;
        ~Arguments();

    protected:
    private:
        std::vector<std::string> _args;
        bool _help;
        bool _debug;
        int _port;
};

#endif /* !ARGUMENTS_HPP_ */
