#include "../../include/server/thread.hpp"

#include "../../include/query_offline/textQuery.hpp"

using namespace std;

namespace ty
{

namespace current_thread
{
__thread int __thread_number;
}

struct ThreadData {
    ThreadData(int thread_number, const ThreadCallback& cb)
    : _thread_number(thread_number)
    , _cb(cb) {}

    void runInThread() {
        current_thread::__thread_number = _thread_number;
        if(_cb) _cb();
    }

    int _thread_number;
    ThreadCallback _cb;
};


Thread::Thread(ThreadCallback&& cb, int __thread_number)
: _pth_id(0)
, _is_running(0) 
, _cb(move(cb))
, _thread_number(__thread_number) {}

Thread::~Thread() {
    if(_is_running) pthread_detach(_pth_id);
}

void Thread::start() {
    ThreadData* pdata = new ThreadData(_thread_number, _cb);
    if(pthread_create(&_pth_id, nullptr, threadFnc, pdata)) {
        perror("pthread create");
        return;
    }
    _is_running  = true;
}

void Thread::join() {
    if(_is_running) {
        pthread_join(_pth_id, nullptr);
        _is_running = 0;
    }
}

// static
void* Thread::threadFnc(void* arg) {
    ThreadData* pdata = static_cast<ThreadData*>(arg);
    if(pdata) pdata->runInThread();
    delete pdata;
    return nullptr;
}

} // end of namespace ty