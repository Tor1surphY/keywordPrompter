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

    void unpack() {
        Json::Reader reader;
        Json::Value  val;
        Json::Value  answer;
        if(reader.parse(_msg, val)) {
            answer = val["answer"];
            for(auto& elem : answer) {
                cout << elem.asString() << "  ";
            }
            cout << endl;
        }
    }

private:
    string _msg;
};
} // end of namespace ty
#endif