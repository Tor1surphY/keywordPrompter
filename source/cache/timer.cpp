#include "../../include/cache/timer.hpp"

#include <sys/timerfd.h>
#include <poll.h>
#include <unistd.h>

namespace ty
{

Timer::Timer(int initial_time, int interval_time, TimerCallback&& cb)
: _timer_fd(createTimerFd())
, _initial_time (initial_time)
, _interval_time(interval_time)
, _cb(move(cb))
, _is_running(false) {}

Timer::~Timer() {
    if(_is_running == true) {
        stopTiemr();
    }
    ::close(_timer_fd);
}

void Timer::startTiemr() {
    _is_running = true;
    struct pollfd poll_fd;
    poll_fd.fd = _timer_fd;
    poll_fd.events = POLLIN;

    setTimerFd(_initial_time, _interval_time);

    while(_is_running == true) {
        int ret = ::poll(&poll_fd, 1, 5000);
        if(ret == -1 && errno == EINTR)
            continue;
        else if(ret == -1) {
            perror("poll");
            exit(1);
        }
        else if(ret == 0) {}
        else {
            if(poll_fd.revents & POLLIN) {
                handleRead();
                if(_cb) _cb();
            }
        }
    }
}

void Timer::stopTiemr() {
    if(_is_running == true) {
        _is_running = false;
        setTimerFd(0, 0);
    }
}

int Timer::createTimerFd() {
    int timer_fd = ::timerfd_create(CLOCK_REALTIME, 0);
    if(timer_fd < 0) {
        perror("timerfd_create");
        exit(1);
    }
    return timer_fd;
}

void Timer::setTimerFd(int inial_time, int interval_time) {
    struct itimerspec value;
    value.it_value.tv_sec     = inial_time;
    value.it_value.tv_nsec    = 0;
    value.it_interval.tv_sec  = interval_time;
    value.it_interval.tv_nsec = 0;
    int ret = ::timerfd_settime(_timer_fd, 0, &value, nullptr);
    if(ret < 0) {
        perror("timer_settime");
        exit(1);
    }
}

void Timer::handleRead() {
    uint64_t how_many = 0;
    int ret = ::read(_timer_fd, &how_many, sizeof(how_many));
    if(ret != sizeof(how_many)) {
        perror("read");
        exit(1);
    }
}
} // end of namespace ty