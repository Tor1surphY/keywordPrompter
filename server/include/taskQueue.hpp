#ifndef __TY_TASKQUEUE_H__
#define __TY_TASKQUEUE_H__

#include "task.hpp"
#include "mutexLock.hpp"
#include "condition.hpp"

#include <queue>

using namespace std;

namespace ty {

using CustomType = Task;

class TaskQueue {
public:
    TaskQueue(size_t);

    bool isEmpty() const { return (_task_queue.size()) == 0; }
    bool isFull()  const { return (_task_queue.size()) == _task_size; }
    size_t size()  const { return _task_queue.size(); }

    void push(CustomType);
    CustomType pop();

    void weakup();

private:
    size_t _task_size;
    queue<CustomType> _task_queue;
    MutexLock _mutex;
    Condition _not_full;    // producer
    Condition _not_empty;    // consumer
    bool _flag;
};

} // end of namespace ty
#endif