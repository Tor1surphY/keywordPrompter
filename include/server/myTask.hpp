#include "tcpConnection.hpp"
#include "thread.hpp"

#include "../query_offline/queryImplement.hpp"
#include "../query_offline/textQuery.hpp"

#include "../../source/query_offline/queryImplement.cpp"

#include <iostream>
#include <bitset>

using namespace std;

namespace ty
{
class MyTask {
public:
    MyTask(const string& msg, const TcpConnectionPtr& connection) 
    : _msg(msg)
    , _connection(connection) {}

    void process(TextQuery* p_text_query) {
        cout << "thread " << current_thread::name << " compute" << endl;
        // _connection->send(_msg);
        // we only do:
            // decode
            // compute
            // encode
        // in thread
        // send back can not run in threadpool
        // it has to be ran in eventloop
        // IO thread and compute thread
        // should only do there own job
        string ans;
        QueryImplement query(_msg, p_text_query);
        ans = query.promote();
        bitset<32> size = ans.size();
        _connection->sendInLoop(size.to_string() + ans);
        // weakup()
        // setCallback() in eventloop
    }

private:
    string _msg;
    const TcpConnectionPtr& _connection;
};
} // end of namespace ty