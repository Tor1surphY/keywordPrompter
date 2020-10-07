#ifndef __TY_TASK_H__
#define __TY_TASK_H__

#include <functional>

namespace ty
{

using Task = std::function<void()>;
} // end of namespace ty
#endif