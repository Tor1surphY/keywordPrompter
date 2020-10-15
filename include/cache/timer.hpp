#ifndef __TY_TIMER_H__
#define __TY_TIMER_H__

#include <functional>

using namespace std;

namespace ty
{

using TimerCallback = function<void()>;

class Timer {
public:
    Timer(int, int, TimerCallback&&);
    ~Timer();

    void startTiemr();
    void stopTiemr();

private:
    int createTimerFd();
    void setTimerFd(int, int);

    void handleRead();

private:
    int _timer_fd;
    int _initial_time;
    int _interval_time;
    TimerCallback _cb;
    bool _is_running;
};
} // end of namespace ty
#endif