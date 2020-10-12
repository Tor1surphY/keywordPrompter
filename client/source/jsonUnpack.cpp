#include "../include/jsonUnpack.hpp"

#include <iostream>

using std::cout;
using std::endl;

namespace ty
{

JsonUnpack::JsonUnpack(const string& msg)
: _msg(msg) {}

string JsonUnpack::unpack() {
    Json::Reader reader;
    if(!reader.parse(_msg, _data)) {
        perror("parse");
        exit(1);
    }
    cout << _data << endl;
}
} // end of namsespace