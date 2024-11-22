/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Server
*/

#ifndef Server_HPP_
#define Server_HPP_

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
    }
}

#endif /* !Server_HPP_ */
