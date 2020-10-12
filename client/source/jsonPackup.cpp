#include "../include/jsonPackup.hpp"

namespace ty
{

JsonPackup::JsonPackup(const string& msg)
: _msg(msg) {}

string JsonPackup::packup() {
    _data_bag = _msg;
    return _data_bag.toStyledString();
}
} // end of namespace ty