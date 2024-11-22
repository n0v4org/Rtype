/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Server
*/

#ifndef SERVER_INCLUDE_NETWORKING_SERVER_HPP_
#define SERVER_INCLUDE_NETWORKING_SERVER_HPP_

namespace rtype {
    namespace net {
        class Server {
            public:
                Server(int, bool);
                ~Server();

            protected:
            private:
                int _port;
                bool _debug;
        };
    } // namespace net
} // namespace rtype

#endif /* !SERVER_INCLUDE_NETWORKING_SERVER_HPP_ */
