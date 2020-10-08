#ifndef __TY_ACCEPTER_HPP__
#define __TY_ACCEPTER_HPP__

#include "socket.hpp"
#include "inetAddr.hpp"

namespace ty
{

class Accepter {
public:
    Accepter(unsigned short);
    Accepter(const string&, unsigned short);

    void readyToListen();

    int accept();
    int fd() const { return _listen_sock.fd(); }

private:
    void setReuseAddr(int);
    void setReusePort(int);

    void listen();
    void bind();

private:
    Socket _listen_sock;
    InetAddr _inet_addr;
};
} // end of namespace ty
#endif