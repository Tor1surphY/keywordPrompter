#ifndef __TY_EVENTLOOP_H__
#define __TY_EVENTLOOP_H__

#include "cannotCopy.hpp"
#include "tcpConnection.hpp"
#include "mutexLock.hpp"

#include <sys/epoll.h>

#include <vector>
#include <map>
#include <memory>
#include <functional>

using namespace std;

namespace ty
{

class Accepter;
class TcpConnection;
using TcpConnectionPtr = shared_ptr<TcpConnection>;
using TcpConnectionCallback = function<void(const TcpConnectionPtr& connection)>;
using Functor = function<void()>;

class EventLoop
: CannotCopy {
public:
    EventLoop(Accepter&);
    ~EventLoop();

    void startLoop();
    void stopLoop();

    void runInLoop(Functor&&);

    void setConnectionCallback(TcpConnectionCallback&& cb)
    { _on_connection = move(cb); }
    void setMessageCallback(TcpConnectionCallback&& cb)
    { _on_message    = move(cb); }
    void setCloseCallback(TcpConnectionCallback&& cb)
    { _on_close      = move(cb); }

private:
    void waitEpollFd();
    void handleNewConnection();
    void handleMessage(int);

    int createEpollFd();
    int createEventFd();

    void addEpollReadFd(int);
    void removeEpollReadFd(int);

    void handleRead();
    void weakup();

    void runPendingFunctors();

private:
    int _epoll_fd;
    int _event_fd;
    bool _is_running;
    Accepter& _accepter;
    map<int, TcpConnectionPtr> _connection_map;
    vector<struct epoll_event> _event_list;
    vector<Functor> _pending_functors;
    MutexLock _mutex;

    TcpConnectionCallback _on_connection;
    TcpConnectionCallback _on_message;
    TcpConnectionCallback _on_close;
};
} // end of namespace ty
#endif