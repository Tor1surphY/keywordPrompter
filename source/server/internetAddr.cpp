#include "../../include/server/inetAddr.hpp"

#include <string.h>

using namespace std;

namespace ty
{
InetAddr::InetAddr(unsigned short port) {
    ::memset(&_sock_addr, 0, sizeof(struct sockaddr_in));
    _sock_addr.sin_family      = AF_INET;
    _sock_addr.sin_port        = ::htons(port);
    _sock_addr.sin_addr.s_addr = INADDR_ANY; // local host ip
}

InetAddr::InetAddr(const string& ip, unsigned short port) {
    ::memset(&_sock_addr, 0, sizeof(struct sockaddr_in));
    _sock_addr.sin_family      = AF_INET;
    _sock_addr.sin_port        = ::htons(port);
    _sock_addr.sin_addr.s_addr = inet_addr(ip.c_str());
}

InetAddr::InetAddr(const struct sockaddr_in& sock_addr)
: _sock_addr(sock_addr) {}

string InetAddr::ip() const {
    return string(inet_ntoa(_sock_addr.sin_addr));
}

unsigned short InetAddr::port() const {
    return ntohs(_sock_addr.sin_port);
}
} // end of namespace ty