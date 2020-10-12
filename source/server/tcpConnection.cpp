#include "../../include/server/tcpConnection.hpp"

#include <string.h>

#include <iostream>
#include <sstream>
#include <bitset>

using namespace std;

namespace ty
{

TcpConnection::TcpConnection(int fd, EventLoop* event_loop)
: _sock(fd)
, _sock_io(fd)
, _local_addr(getLocalAddr(fd))
, _peer_addr(getPeerAddr(fd))
, _is_shutdown_write(false)
, _event_loop(event_loop) {}

TcpConnection::~TcpConnection() {
    if(_is_shutdown_write == false) shutdown();
}

string TcpConnection::recv() {
    char size[32];
    char buff[65535];
    _sock_io.readN(size, 32);
    bitset<32> sz = static_cast<int> (*size);
    cout << sz << endl;
    _sock_io.readN(buff, sz.to_ulong());
    return string(buff);
}

void TcpConnection::send(const string& msg) {
    _sock_io.writeN(msg.c_str(), msg.size());
}

void TcpConnection::sendInLoop(const string& msg) {
    if(_event_loop) {
        _event_loop->runInLoop(std::bind(&TcpConnection::send, this, msg));
    }
}

void TcpConnection::shutdown() {
    if(_is_shutdown_write == false) {
        _is_shutdown_write = true;
        _sock.shutdownWrite();
    }
}

InetAddr TcpConnection::getLocalAddr(int fd) {
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr_in);
    if(getsockname(
        _sock.fd(), 
        (struct sockaddr*) &addr, 
        &len
    ) == -1) {
        perror("getsockname");
        exit(1);
    }
    return InetAddr(addr);
}

InetAddr TcpConnection::getPeerAddr(int fd) {
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr_in);
    if(getpeername(
        _sock.fd(), 
        (struct sockaddr*) &addr, 
        &len
    ) == -1) {
        perror("getsockname");
        exit(1);
    }
    return InetAddr(addr);
}

string TcpConnection::info() const{
    ostringstream oss;
    oss << _local_addr.ip() << ":" << _local_addr.port()
        << " ---> " 
        << _peer_addr.ip()  << ":" << _peer_addr.port();
    return oss.str();
}

void TcpConnection::handleConnectionCallback() {
    if(_on_connection)
        _on_connection(shared_from_this());
}

void TcpConnection::handleMessageCallback() {
    if(_on_message)
        _on_message(shared_from_this());
}

void TcpConnection::handleCloseCallback() {
    if(_on_close)
        _on_close(shared_from_this());
}

void TcpConnection::setToNonBlock() {
    _sock.setToNonBlock();
}

bool TcpConnection::isDisconnected() {
    int ret = -1;
    char buff[1024] = {0};
    do {
        ret = ::recv(_sock.fd(), buff, sizeof(buff), MSG_PEEK);
    } while(ret == -1 && errno == EINTR);
    return ret == 0;

}
} // end of namespace ty