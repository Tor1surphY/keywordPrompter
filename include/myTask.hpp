#include "../include/tcpConnection.hpp"
#include "../include/thread.hpp"

#include <iostream>

using namespace std;

namespace ty
{
class MyTask {
public:
    MyTask(const string& msg, const TcpConnectionPtr& connection) 
    : _msg(msg)
    , _connection(connection) {}

    void process() {
        cout << "thread " << current_thread::name << " send back";
        // _connection->send(_msg);
        // we only do:
            // encode
            // compute
            // decode
        // in thread
        // send back can not run in threadpool
        // it has to be ran in eventloop

        // Io thread and compute thread
        // should only do there own job
        _connection->sendInLoop(_msg);
        // weakup()
        // setCallback() in eventloop
    }

private:
    string _msg;
    const TcpConnectionPtr& _connection;
};
} // end of namespace ty