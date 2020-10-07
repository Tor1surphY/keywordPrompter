#ifndef __TY_CONNECTER_HPP__
#define __TY_CONNECTER_HPP__

#include "inetAddr.hpp"
#include "socket.hpp"

namespace ty
{

class Connecter {
public:
    Connecter(const string&, unsigned short);

    int connect();
    int fd() const { return _connect_sock.fd(); }

private:
    Socket _connect_sock;
    InetAddr _inet_addr;
};
} // end of namespace ty
#endif