#include "../include/eventLoop.hpp"
#include "../include/accepter.hpp"
#include "../include/tcpConnection.hpp"
#include "../include/thread.hpp"

#include <unistd.h>
#include <sys/eventfd.h>

namespace ty
{

EventLoop::EventLoop(Accepter& accepter)
: _epoll_fd(createEpollFd())
, _event_fd(createEventFd())
, _accepter(accepter)
, _is_running(false)
, _event_list(1024) { // _event_list should initalized by config
    addEpollReadFd(_accepter.fd());
    addEpollReadFd(_event_fd);
} 

EventLoop::~EventLoop() {
    close(_epoll_fd);
}

void EventLoop::startLoop() {
    if(_is_running == false) {
        _is_running = true;
        while(_is_running == true) {
            waitEpollFd();
        }
    }
}

void EventLoop::stopLoop() {
    if(_is_running == true) {
        _is_running = false;
    }
}

void EventLoop::runInLoop(Functor&& cb) {
    {
        AutoMutexLock auto_lock(_mutex);
        _pending_functors.push_back(std::move(cb));
    }
    weakup();
}

void EventLoop::waitEpollFd() {
    int ready_fd_num = 0;
    do {
        ready_fd_num = ::epoll_wait(
            _epoll_fd, 
            &_event_list[0],
            _event_list.size(),
            1024);
    } while(-1 == ready_fd_num && errno == EINTR);

    if(-1 == ready_fd_num) {
        perror("epoll_wait");
        exit(1);
    }
    else if(0 == ready_fd_num) 
        printf("[epoll wait timeout]\n");
    else {
        // event list is not enough to recive fd
        if(ready_fd_num == _event_list.size()) {
            _event_list.resize(2 * ready_fd_num);
        }

        for(int idx = 0; idx != ready_fd_num; ++idx) {
            int ready_fd = _event_list[idx].data.fd;
            if(ready_fd == _accepter.fd()) {
                if(_event_list[idx].events & EPOLLIN)
                    handleNewConnection();
            }
            else if(ready_fd == _event_fd) {
                // compute thread notice that IO thread to run futher
                handleRead();
                // printf("run pending functors\n");
                runPendingFunctors();
            }
            else {
                if(_event_list[idx].events & EPOLLIN)
                    handleMessage(ready_fd);
            }
        }
    }
}

void EventLoop::handleNewConnection() {
    int peer_fd = _accepter.accept();
    addEpollReadFd(peer_fd);
    TcpConnectionPtr new_connection(new TcpConnection(peer_fd, this));

    new_connection->setConnectionCallback(_on_connection);
    new_connection->setMessageCallback(_on_message);
    new_connection->setCloseCallback(_on_close);
    new_connection->setToNonBlock();
    _connection_map.insert(make_pair(peer_fd, new_connection));
    
    new_connection->handleConnectionCallback();
}

void EventLoop::handleMessage(int fd) {
    auto iter = _connection_map.find(fd);
    if(iter->second->isDisconnected() == true) {
        iter->second->handleCloseCallback();
        removeEpollReadFd(fd);
        _connection_map.erase(iter);
    }
    else 
        iter->second->handleMessageCallback();
}

int EventLoop::createEpollFd() {
    int epoll_fd = ::epoll_create1(0);
    if(-1 == epoll_fd) {
        perror("epoll_create1");
        exit(0);
    }
    return epoll_fd;
}

int EventLoop::createEventFd() {
    int event_fd = ::eventfd(0, 0);
    if(event_fd < 0) {
        perror("eventfd");
        exit(1);
    }
    return event_fd;
}

void EventLoop::handleRead() {
    uint64_t howmany = -1;
    int ret = ::read(_event_fd, &howmany, sizeof(howmany));
    if(ret != sizeof(howmany)) {
        perror("read");
        exit(1);
    }
}

void EventLoop::weakup() {
    uint64_t one = 1;
    int ret = ::write(_event_fd, &one, sizeof(one));
    if(ret != sizeof(one)) {
        perror("write");
        exit(1);
    }
}

void EventLoop::runPendingFunctors() {
    vector<Functor> tmp;
    {
        AutoMutexLock auto_lock(_mutex);
        tmp.swap(_pending_functors);
    }
    for(auto& functor : _pending_functors) {
        functor();
    }
}

void EventLoop::addEpollReadFd(int fd) {
    struct epoll_event value;
    value.data.fd = fd;
    value.events = EPOLLIN;
    int ret = epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, fd, &value);
    if(-1 == ret) {
        perror("cpoll_ctl");
        exit(1);
    }
}

void EventLoop::removeEpollReadFd(int fd) {
    struct epoll_event value;
    value.data.fd = fd;
    value.events = EPOLLIN;
    int ret = epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, fd, &value);
    if(-1 == ret) {
        perror("cpoll_ctl");
        exit(1);
    }
}
} // end of namespace ty