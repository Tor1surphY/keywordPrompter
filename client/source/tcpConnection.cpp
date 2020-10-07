#include "../include/tcpConnection.hpp"

#include <string.h>

#include <iostream>
#include <sstream>
using namespace std;

namespace ty
{

TcpConnection::TcpConnection(int fd)
: _sock(fd)
, _sock_io(fd)
, _local_addr(getLocalAddr(fd))
, _peer_addr(getPeerAddr(fd))
, _is_shutdown_write(false) {}

TcpConnection::~TcpConnection() {
    if(_is_shutdown_write == false) shutdown();
}

string TcpConnection::recv() {
    char buff[65535];
    _sock_io.readLine(buff, sizeof(buff));
    return string(buff);
}

void TcpConnection::send(const string& msg) {
    _sock_io.writeN(msg.c_str(), msg.size());
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
        perror("getpeername");
        exit(1);
    }
    return InetAddr(addr);
}

string TcpConnection::info() const{
    ostringstream oss;
    oss << _local_addr.ip() << ":" << _local_addr.port()
        << " connected sucessfuly with " 
        << _peer_addr.ip()  << ":" << _peer_addr.port() << endl;
    return oss.str();
}
} // end of namespace ty