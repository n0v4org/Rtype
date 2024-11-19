/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** ServerError
*/

#ifndef SERVER_INCLUDE_SERVERERROR_HPP_
    #define SERVER_INCLUDE_SERVERERROR_HPP_
    #include <string>
    #include <map>

enum {
    SERVER_INTERNAL_ERROR = 0,
};

static const std::map<int, std::string> ERRORS = {
    {SERVER_INTERNAL_ERROR, "Internal Server Error: "},
};

class ServerError : public std::exception {
    public:
        ServerError(std::string msg, int type) {
            if (ERRORS.find(type) != ERRORS.end()) {
                _msg = ERRORS.at(type) + msg;
            } else {
                _msg = "Unknown Error: " + msg;
            }
        };
        const char * what() const noexcept override {
            return _msg.c_str();
        }

    protected:
    private:
        std::string _msg;
};

#endif /* SERVER_INCLUDE_SERVERERROR_HPP_ */
