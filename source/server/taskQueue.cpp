#include "../../include/server/taskQueue.hpp"

namespace ty
{

TaskQueue::TaskQueue(size_t task_size)
: _task_size(task_size)
, _mutex()
, _not_full(_mutex)
, _not_empty(_mutex)
, _flag(true) {}

void TaskQueue::push(CustomType lmt) {
    AutoMutexLock auto_lock(_mutex);
    // 防止异常唤醒
    while(isFull()) {
        _not_full.wait();
    }
    _task_queue.push(lmt);
    _not_empty.notify();
}

CustomType TaskQueue::pop() {
    AutoMutexLock auto_lock(_mutex);
    while(_flag && isEmpty()) {
        _not_empty.wait();
    }
    if(_flag == true) {
        CustomType lmt = _task_queue.front();
        _task_queue.pop();
        _not_full.notify();
        return lmt;
    }
    else return nullptr;
}

void TaskQueue::weakup() {
    _flag = false;
    _not_empty.notifyAll();
}
} // end of namespace ty