#include "../include/socketIO.hpp"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

namespace ty
{

SocketIO::SocketIO(int fd)
: _fd(fd) {}

int SocketIO::readN(char* buff, int len) {
    int left_len = len;
    char* _buff = buff;
    while(left_len > 0) {
        int ret = ::read(_fd, _buff, left_len);
        if(ret == -1 && errno == EINTR) continue;
		else if(ret == -1) {
			perror("read");
			return len - left_len;
		}
		else if(ret == 0) {
            return len - left_len;
        }
		else {
			left_len -= ret;
			_buff += ret;
		}
    }
    return len - left_len;
}

int SocketIO::writeN(const char* buff, int len) {
    int left_len = len;
    const char* _buff = buff;
    while(left_len > 0) {
        int ret = ::write(_fd, _buff, left_len);
        if(ret == -1 && errno == EINTR) continue;
		else if(ret == -1) {
			perror("read");
			exit(1);
		}
		else {
			left_len -= ret;
			_buff += ret;
		}
    }
    return len - left_len;
}
} // end of namespace ty