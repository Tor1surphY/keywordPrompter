#ifndef __TY_THREADPOOL_H__
#define __TY_THREADPOOL_H__

#include "thread.hpp"
#include "taskQueue.hpp"
#include "task.hpp"
#include "../cache/timerThread.hpp"
#include "../cache/cacheManage.hpp"

#include <memory>

using std::unique_ptr;
using std::vector;

namespace ty
{

class Threadpool {
public:
    Threadpool(size_t, size_t);
    ~Threadpool();

    void start();
    void stop();
    void weakupAll();

    void addTask(Task&&);

    Cache* getCache(int thread_number) {   return _cache_manager.getCache(thread_number);  }
    void updateCache() {    _cache_manager.updateCache();   }

private:
    Task getTask();
    void threadFunc();

private:
    size_t _thread_num;
    size_t _queue_size;
    vector<unique_ptr<Thread>> _threadpool;
    unique_ptr<TimerThread> _timer_thread;
    TaskQueue _task_queue;
    CacheManage _cache_manager;
    bool _exited;
};

} // end of namespace ty
#endif