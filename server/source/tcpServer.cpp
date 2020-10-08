#include "../include/tcpServer.hpp"

namespace ty
{

TcpServer::TcpServer(const string& ip, unsigned short port)
: _accepter(ip, port)
, _event_loop(_accepter) {}

void TcpServer::setConnectionCallback(TcpConnectionCallback&& cb) {
    _event_loop.setConnectionCallback(move(cb));
}
void TcpServer::setMessageCallback(TcpConnectionCallback&& cb) {
    _event_loop.setMessageCallback(move(cb));
}
void TcpServer::setCloseCallback(TcpConnectionCallback&& cb) {
    _event_loop.setCloseCallback(move(cb));
}

void TcpServer::startServer() {
    _accepter.readyToListen();
    _event_loop.startLoop();
}

void TcpServer::stopServer() {
    _event_loop.stopLoop();
}
} // end of namespace