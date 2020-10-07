#ifndef __TY_CONDITION_H__
#define __TY_CONDITION_H__

#include "cannotCopy.hpp"

#include <pthread.h>

namespace ty {

class MutexLock;

class Condition
: CannotCopy {
public:
    Condition(MutexLock&);
    ~Condition();

    void wait();
    void notify();
    void notifyAll();

private:
    pthread_cond_t _cond;
    MutexLock& _mutex;
};

} // end of namespace ty

#endif