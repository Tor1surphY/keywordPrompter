#include "tcpConnection.hpp"
#include "thread.hpp"
#include "jsonUnpack.hpp"

#include "../query_offline/queryImplement.hpp"
#include "../query_offline/textQuery.hpp"
#include "../cache/cacheManage.hpp"

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

    void process(TextQuery* p_text_query, Threadpool* p_threadpool) {
        cout << "thread " << current_thread::__thread_number << " working" << endl;
        string ans;
        Cache* p_cache = p_threadpool->getCache(current_thread::__thread_number);

        ans = p_cache->get(_msg);
        if(ans != "not found") {
            bitset<32> size = ans.size();
            _connection->sendInLoop(size.to_string() + ans);
            cout << "found in cache" << endl;
        }
        else {
            QueryImplement query(_msg, p_text_query);
            ans = query.promote();
            p_cache->put(_msg, ans);
            bitset<32> size = ans.size();
            _connection->sendInLoop(size.to_string() + ans);
            cout << "found in RAM" << endl;
        }
    }

private:
    string _msg;
    const TcpConnectionPtr& _connection;
};
} // end of namespace ty