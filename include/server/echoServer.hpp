#ifndef __TY_ECHOSERVER_H__
#define __TY_ECHOSERVER_H__

#include "tcpConnection.hpp"
#include "threadpool.hpp"
#include "tcpServer.hpp"

#include <string>
#include <memory>

namespace ty
{



class EchoServer {
public:
    using TcpConnectionPtr = shared_ptr<TcpConnection>;
    using TcpConnectionCallback = function<const void(TcpConnectionPtr& connection)>;

    EchoServer();
    EchoServer(int, int, const string&, unsigned int);

    void start();
    void stop();

    void onConnection(const TcpConnectionPtr&);
    void onMessage(const TcpConnectionPtr&);
    void onClose(const TcpConnectionPtr&);

private:
    Threadpool _threadpool;
    TcpServer _server;
};
} // end of namespace ty
#endif