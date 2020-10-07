#ifndef __TY_SOCKRT_H__
#define __TY_SOCKRT_H__

namespace ty
{

class Socket {
public:
    Socket();
    explicit
    Socket(int);
    ~Socket();

    void setToNonBlock();

    int fd() const { return _fd; }
    // when peer side disconnected there may some data left
    // that we are not quickly enough to recive.
    // so we only shutdown write side
    // so that we can make sure we will recive all data
    void shutdownWrite();

private:
    int _fd;
};
} // end of namespace ty
#endif