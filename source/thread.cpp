#include "../include/thread.hpp"

using namespace std;

namespace ty
{

namespace current_thread
{
__thread const char* name = "ty thread";
}

struct ThreadData {
    ThreadData(const string& name, const ThreadCallback& cb)
    : _name(name)
    , _cb(cb) {}

    void runInThread() {
        current_thread::name = ((_name == string()) ? "ty thread"
                                                    :  _name.c_str());
        if(_cb) _cb();
    }

    string _name;
    ThreadCallback _cb;
};


Thread::Thread(ThreadCallback&& cb, const string& name)
: _pth_id(0)
, _is_running(0) 
, _cb(move(cb))
, _name(name) {}

Thread::~Thread() {
    if(_is_running) pthread_detach(_pth_id);
}

void Thread::start() {
    ThreadData* pdata = new ThreadData(_name, _cb);
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