#include "../include/accepter.hpp"

#include <sys/types.h>
#include <sys/socket.h>

#include <iostream>

using std::cout;
using std::endl;

namespace ty
{

Accepter::Accepter(unsigned short port)
: _inet_addr(port)
, _listen_sock() {}

Accepter::Accepter(const string& ip, unsigned short port)
: _inet_addr(ip, port)
, _listen_sock(){}

void Accepter::readyToListen() {
    setReuseAddr(true);
    setReusePort(true);
    bind();
    cout << "[server started]" << endl;
    listen();
}

void Accepter::setReuseAddr(int opt) {
    int _opt = opt;
	if(setsockopt(
        _listen_sock.fd(), 
        SOL_SOCKET, 
        SO_REUSEADDR, 
        (const void*) &_opt, 
        sizeof(_opt)
    ) == -1) {
        perror("setsockopt");
        exit(1);
    }
}

void Accepter::setReusePort(int opt) {
    int _opt = opt;
    if(setsockopt(
        _listen_sock.fd(),
        SOL_SOCKET, 
        SO_REUSEPORT, 
        (const void*) &_opt, 
        sizeof(_opt)
    ) == -1) {
        perror("setsockopt");
        exit(1);
    }
}

void Accepter::bind() {
    int ret = ::bind(
        _listen_sock.fd(), 
		(struct sockaddr *)_inet_addr.getInetAddrPtr(),
		sizeof(struct sockaddr)
    );
	if(-1 == ret) perror("bind");
}

void Accepter::listen() {
    int ret = ::listen(_listen_sock.fd(), 10);
	if(-1 == ret) perror("listen");
}

int Accepter::accept() {
    int new_fd = ::accept(_listen_sock.fd(), NULL, NULL);
	if(new_fd == -1) perror("accept");
	return new_fd;
}
} // end of namespace ty