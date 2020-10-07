#ifndef __TY_CANNOTCOPY_H__
#define __TY_CANNOTCOPY_H__

namespace ty {

class CannotCopy {
protected:
    CannotCopy() {}
    ~CannotCopy() {}

    CannotCopy(const CannotCopy&) = delete;
    CannotCopy& operator=(const CannotCopy&) = delete;
};

} // end of namespace ty
#endif