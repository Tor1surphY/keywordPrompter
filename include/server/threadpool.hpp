#ifndef __TY_THREADPOOL_H__
#define __TY_THREADPOOL_H__

#include "thread.hpp"
#include "taskQueue.hpp"
#include "task.hpp"

#include <memory>

using namespace std;

namespace ty
{

class Threadpool {
    friend class WorkerThread;
public:
    Threadpool(size_t, size_t);
    ~Threadpool();

    void start();
    void stop();
    void weakupAll();

    void addTask(Task&&);

private:
    Task getTask();
    void threadFunc();

private:
    size_t _thread_num;
    size_t _queue_size;
    vector<unique_ptr<Thread>> _threadpool;
    TaskQueue _task_queue;
    bool _exited;
};

} // end of namespace ty
#endif