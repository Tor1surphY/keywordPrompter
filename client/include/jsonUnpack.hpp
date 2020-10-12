#ifndef __TY_JSONUNPACK_H__
#define __TY_JSONUNPACK_H__

#include <json/json.h>

#include <string>

using std::string;

namespace ty
{

class JsonUnpack {
public:
    JsonUnpack(const string&);
    string unpack();

private:
    string _msg;
    Json::Value _data;
};
} // end of namespace ty
#endif