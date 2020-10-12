#include "../../include/server/echoServer.hpp"
#include "../../include/server/myTask.hpp"

#include "../query_offline/textQuery.cpp"

#include <iostream>

using namespace std;

namespace ty
{

EchoServer::EchoServer(int thread_num, int pool_size, const string& ip, unsigned int port, const string& path)
: _threadpool(thread_num, pool_size)
, _server(ip, port)
, _path(path) {
    _server.setConnectionCallback(std::bind(&EchoServer::onConnection, this, std::placeholders::_1));
    _server.setMessageCallback(std::bind(&EchoServer::onMessage, this, std::placeholders::_1));
    _server.setCloseCallback(std::bind(&EchoServer::onClose, this, std::placeholders::_1));
    _p_text_query = TextQuery::getInstance(_path);
}

void EchoServer::start() {
    _p_text_query->loadData();
    _threadpool.start();
    _server.startServer();
}

void EchoServer::stop() {
    _server.stopServer();
}

void EchoServer::onConnection(const TcpConnectionPtr& connection) {
    cout << "[" << connection->info() << " connected successed]" << endl;
}

void EchoServer::onMessage(const TcpConnectionPtr& connection) {
    string msg = connection->recv();
    cout << "server recived: " << msg;
    MyTask task(msg, connection);
    _threadpool.addTask(bind(&MyTask::process, task, _p_text_query));
}

void EchoServer::onClose(const TcpConnectionPtr& connection) {
    cout << "[" << connection->info() << " connection closed]" << endl;
}


} // end of namespace ty