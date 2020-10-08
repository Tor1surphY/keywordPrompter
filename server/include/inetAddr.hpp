#ifndef __TY_INTERADDR_H__
#define __TY_INTERADDR_H__

#include <arpa/inet.h>
#include <string>

using namespace std;

namespace ty
{
class InetAddr{
public:
    explicit
    InetAddr(unsigned short);
    InetAddr(const string&, unsigned short);
    InetAddr(const struct sockaddr_in&);
    
    string ip() const;
    unsigned short port() const;
    struct sockaddr_in* getInetAddrPtr() { return& _sock_addr; }
    
private:
    struct sockaddr_in _sock_addr;
};
} // end of namespace ty
#endif