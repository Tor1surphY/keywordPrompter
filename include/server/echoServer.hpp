#ifndef __TY_ECHOSERVER_H__
#define __TY_ECHOSERVER_H__

#include "tcpConnection.hpp"
#include "threadpool.hpp"
#include "tcpServer.hpp"

#include "../query_offline/queryImplement.hpp"
#include "../query_offline/textQuery.hpp"

#include <string>
#include <memory>

namespace ty
{

class EchoServer {
public:
    using TcpConnectionPtr = shared_ptr<TcpConnection>;
    using TcpConnectionCallback = function<const void(TcpConnectionPtr& connection)>;

    EchoServer();
    EchoServer(int, int, const string&, unsigned int, const string&);

    void start();
    void stop();

    void onConnection(const TcpConnectionPtr&);
    void onMessage(const TcpConnectionPtr&);
    void onClose(const TcpConnectionPtr&);

private:
    Threadpool _threadpool;
    TcpServer _server;
    string _path;
    TextQuery* _p_text_query;
};
} // end of namespace ty
#endif