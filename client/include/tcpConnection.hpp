#ifndef __TY_TCPCONNECTION_H__
#define __TY_TCPCONNECTION_H__

#include "inetAddr.hpp"
#include "socketIO.hpp"
#include "socket.hpp"
#include "cannotCopy.hpp"

namespace ty
{

class TcpConnection 
: CannotCopy {
public:
    TcpConnection(int);
    ~TcpConnection();

    string recv();
    void send(const string&);

    string info() const;

private:
    void shutdown();

    InetAddr getLocalAddr(int);
    InetAddr getPeerAddr(int);

    int convertToInt(string);

private:
    Socket   _sock;
    SocketIO _sock_io;
    InetAddr _local_addr;
    InetAddr _peer_addr;
    bool _is_shutdown_write;
};
} // end of namespace ty
#endif