#ifndef __TY_TIMERTHREAD_H__
#define __TY_TIMERTHREAD_H__

#include "timer.hpp"
#include "../server/thread.hpp"

#include <memory>

using std::unique_ptr;

namespace ty
{

class TimerThread {
public:
    TimerThread(int initial_time, int interval_time, TimerCallback&& cb, int thread_number)
    : _tiemr(initial_time, interval_time, move(cb))
    , _thread(bind(&Timer::startTiemr, &_tiemr), thread_number) {}

    void start() { _thread.start(); }
    void stop() {
        _tiemr.stopTiemr();
        _thread.join();
    }

    static void timerFunc();

private:
    Timer _tiemr;
    Thread _thread;
};
} // end of namespace ty
#endif