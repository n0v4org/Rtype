/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Lobby
*/

#ifndef SERVER_INCLUDE_NETWORKING_LOBBY_HPP_
#define SERVER_INCLUDE_NETWORKING_LOBBY_HPP_
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace rtype {
  namespace net {

class Lobby {
    public:
        Lobby(boost::asio::io_context& io_context);
        ~Lobby();

    protected:
    private:
};

  }  // namespace net
}  // namespace rtype


#endif  // SERVER_INCLUDE_NETWORKING_LOBBY_HPP_
