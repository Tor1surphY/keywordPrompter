#ifndef __TY_JSONUNPACK_H__
#define __TY_JSONUNPACK_H__

#include <json/json.h>

#include <string>

using std::string;

namespace ty
{

class JsonUnpack {
public:
    JsonUnpack(const string& msg)
    : _msg(msg) {}

    string unpack() {
        Json::Reader reader;
        Json::Value  val;
        Json::Value  answer;
        string ret;
        if(reader.parse(_msg, val)) {
            answer = val["answer"];
            for(auto& elem : answer) {
                ret += elem.asString() + "  ";
            }
        }
        return ret;
    }

private:
    string _msg;
};
} // end of namespace ty
#endif