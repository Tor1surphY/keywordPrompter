#ifndef __TY_JSONPACKUP_H__
#define __TY_JSONPACKUP_H__

#include <json/json.h>

#include <string>

using std::string;

namespace ty
{
class JsonPackup {
public:
    JsonPackup(const string&);
    string packup();

private:
    string _msg;
    Json::Value _data_bag;
};
} // end of namespace ty
#endif