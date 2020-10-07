#ifndef __TY_TCPSERVER_H__
#define __TY_TCPSERVER_H__

#include "accepter.hpp"
#include "eventLoop.hpp"

#include <string>

using namespace std;

namespace ty
{

class TcpServer {
public:
    TcpServer(const string&, unsigned short);

    void startServer();
    void stopServer();

    void setConnectionCallback(TcpConnectionCallback&&);
    void setMessageCallback(TcpConnectionCallback&&);
    void setCloseCallback(TcpConnectionCallback&&);

private:
    Accepter _accepter;
    EventLoop _event_loop;
};
} // end of namespace ty
#endif