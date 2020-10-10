#ifndef __TY_MUTEXLOCK_H__
#define __TY_MUTEXLOCK_H__

#include "cannotCopy.hpp"

#include <pthread.h>

namespace ty {

class MutexLock
: CannotCopy {
public:
    MutexLock();
    ~MutexLock();

    void lock();
    void unlock();
    bool isLocked() const { return _is_locked; }
    pthread_mutex_t* getMutexLockPtr() { return &_mutex; }

private:
    pthread_mutex_t _mutex;
    bool _is_locked;
};

class AutoMutexLock {
public:
    AutoMutexLock(MutexLock& mutex)
    : _mutex(mutex) { _mutex.lock(); }

    ~AutoMutexLock() { _mutex.unlock(); }

private:
    MutexLock& _mutex;
};

} // end of namespace ty

#endif