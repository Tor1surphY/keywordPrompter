#include "../../include/server/socketIO.hpp"

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
			perror("write");
			return len - left_len;
		}
		else {
			left_len -= ret;
			_buff += ret;
		}
    }
    return len - left_len;
}

int SocketIO::recvPeek(char* buff, int len) {
    int ret;
    do {
        // recive without move data from fd
        // just check how many data we will recive
        ret = ::recv(_fd, buff, len, MSG_PEEK);
    } while(ret == -1 && errno == EINTR);
    return ret;
}

int SocketIO::readLine(char* buff, int max_len) {
    int left_len = max_len - 1;
    char* _buff = buff;
    int line_len = 0;
    while(left_len > 0) {
        int ret = recvPeek(_buff, left_len);
        if(ret > 0) {
            for(int idx = 0; idx < ret; ++idx) {
                // if got a '\n', read all data before '\n' and '\n'
                if(_buff[idx] == '\n') {
                    int len = idx + 1;
                    readN(_buff, len);
                    line_len += len;
                    _buff += len;
                    // add '\0' after '\n'
                    *_buff = '\0';
                    return line_len;
                }
            }
            // if not got '\n', read all data and continue
            readN(_buff, ret);
            left_len -= ret;
            _buff += ret;
            line_len += ret;
        }
        else if(0 == ret) break;
    }
    // '\0' is the end of data
    *_buff = '\0';
    return line_len;
}
} // end of namespace ty