#ifndef __TY_TEXTQUERY_H__
#define __TY_TEXTQUERY_H__

#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <map>

using std::map;
using std::string;
using std::vector;
using std::shared_ptr;

namespace ty
{

class TextQuery {
public:
    friend class QueryImplement;

    static TextQuery* getInstance(const string& path) {
        if(_p_instance == nullptr) {
            _p_instance = new TextQuery(path);
        }
        return _p_instance;
    }
    static void destory() {
        if(_p_instance != nullptr) {
            delete _p_instance;
            _p_instance = nullptr;
        }
    }

    void loadData();

private:
    TextQuery(const string& path)
    : _path(path) {}

private:
    static TextQuery* _p_instance;

    string _path;
    map<string, int> _dic;
    map<char, vector<string>> _idx;
};
} // end of namespace ty
#endif