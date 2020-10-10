#include "../../include/server/socket.hpp"

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <iostream>

namespace ty
{

Socket::Socket() {
    _fd = socket(AF_INET, SOCK_STREAM, 0);
	if(_fd == -1) {
		perror("socket");
	}
}

Socket::Socket(int fd) 
:_fd(fd) {}

Socket::~Socket() {
    ::close(_fd);
}

void Socket::setToNonBlock() {
    int flag = ::fcntl(_fd, F_GETFL, 0);
    if(flag < 0) {
        perror("fcntl");
        exit(1);
    }
    flag |= O_NONBLOCK;
    int ret = ::fcntl(_fd, F_SETFL, flag);
    if(ret < 0) {
        perror("fcntl");
        exit(1);
    }
}

void Socket::shutdownWrite() {
    ::shutdown(_fd, SHUT_WR);
}
} // end of namespace ty