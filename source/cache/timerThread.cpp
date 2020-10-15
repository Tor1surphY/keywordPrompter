#include "../../include/cache/timerThread.hpp"

#include <iostream>

using std::cout;
using std::endl;

namespace ty
{

// static
void timerFunc(Threadpool* p_threadpool) {
    p_threadpool->updateCache();
}
} // end of namespace ty