#include "../../include/server/threadpool.hpp"

#include <unistd.h>

namespace ty
{

Threadpool::Threadpool(size_t thread_num, size_t queue_size)
: _thread_num(thread_num)
, _queue_size(queue_size)
, _task_queue(_queue_size)
, _threadpool()
, _exited(false) {
    _threadpool.reserve(_thread_num); // 开辟空间
}

Threadpool::~Threadpool() {
    if(_exited == false) stop();
}

void Threadpool::start() {
    for(size_t idx = 0; idx != _thread_num; ++idx) {
        unique_ptr<Thread> thread(new Thread(
            bind(&Threadpool::threadFunc, this),
            idx
        ));
        _threadpool.push_back(move(thread));
    }

    unique_ptr<Thread> timer_thread(new Thread(bind(&Timer::start(), this, _thread_num));
    _threadpool.push_back(timer_thread);


    for(auto& thread : _threadpool) thread->start();
}

void Threadpool::stop() {
    if(_exited == false) {
        // 1. 如果任务队列为空，那么就等待所有的线程执行任务完毕
        while(_task_queue.isEmpty() == false) sleep(3);
        // 2. 如果子线程执行过快，那么在设置为true之前，就会进入wait并阻塞了
        _exited = true;
        // 3. 唤醒所有子线程
        weakupAll();
        // 4. 回收所有子线程
        for(auto& thread : _threadpool) thread->join();
    }
}

void Threadpool::weakupAll() {
    _task_queue.weakup();
}

void Threadpool::addTask(Task&& task) {
    _task_queue.push(task);
}

Task Threadpool::getTask() {
    return _task_queue.pop();
}

void Threadpool::threadFunc() {
    while(_exited == false) {
        Task task = getTask();
        if(task) {
            task();
        }
    }
}

} // end of namespace ty