#ifndef __TY_SOCKETIO_HPP__
#define __TY_SOCKETIO_HPP__

namespace ty
{

class SocketIO {
public:
    SocketIO(int);
    
    int readN(char*, int);
    int writeN(const char*, int);
    int fd() const {    return _fd; }
    
private:
    int _fd;
};
} // end of namespace ty
#endif