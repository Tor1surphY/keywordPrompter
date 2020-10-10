#ifndef __TY_PC_H__
#define __TY_PC_H__

#include "taskQueue.hpp"

namespace ty
{

class TaskQueue;

class Producer {
public:
    void produce(TaskQueue&);
};

class Consumer {
public:
    void consume(TaskQueue&);
};
} // end of namespace ty
#endif