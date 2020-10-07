#include "../include/connecter.hpp"

namespace ty
{

Connecter::Connecter(const string& ip, unsigned short port)
: _inet_addr(ip, port)
, _connect_sock() {}

int Connecter::connect() {
    int ret = ::connect(
        _connect_sock.fd(), 
        (struct sockaddr*) _inet_addr.getInetAddrPtr(),
        sizeof(*(_inet_addr.getInetAddrPtr()))
    );
    if(-1 == ret) {
        perror("connect");
        exit(0);
    }
    return ret;
}
} // end of namespace ty