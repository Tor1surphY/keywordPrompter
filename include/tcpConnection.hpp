#ifndef __TY_TCPCONNECTION_HPP__
#define __TY_TCPCONNECTION_HPP__

#include "inetAddr.hpp"
#include "socketIO.hpp"
#include "socket.hpp"
#include "cannotCopy.hpp"
#include "eventLoop.hpp"

#include <memory>
#include <functional>

using namespace std;

namespace ty
{

class EventLoop;
class TcpConnection;

using TcpConnectionPtr = shared_ptr<TcpConnection>;
using TcpConnectionCallback = function<void(const TcpConnectionPtr& connection)>;

class TcpConnection 
: CannotCopy
, public enable_shared_from_this<TcpConnection> {
public:

    TcpConnection(int, EventLoop*);
    ~TcpConnection();

    string recv();
    void send(const string&);
    void sendInLoop(const string&);

    string info() const;

    void setConnectionCallback(const TcpConnectionCallback& cb)
    { _on_connection = cb; }
    void setMessageCallback(const TcpConnectionCallback& cb)
    { _on_message    = cb; }
    void setCloseCallback(const TcpConnectionCallback& cb)
    { _on_close      = cb; }

    void handleConnectionCallback();
    void handleMessageCallback();
    void handleCloseCallback();

    bool isDisconnected();

    void setToNonBlock();

private:
    void shutdown();

    InetAddr getLocalAddr(int);
    InetAddr getPeerAddr(int);

private:
    Socket   _sock;
    SocketIO _sock_io;
    InetAddr _local_addr;
    InetAddr _peer_addr;
    bool _is_shutdown_write;
    EventLoop* _event_loop;

    TcpConnectionCallback _on_connection;
    TcpConnectionCallback _on_message;
    TcpConnectionCallback _on_close;
};
} // end of namespace ty
#endif