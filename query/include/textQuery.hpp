#ifndef __TY_TEXTQUERY_H__
#define __TY_TEXTQUERY_H__

#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <set>

using std::set;
using std::map;
using std::string;
using std::vector;
using std::shared_ptr;
using std::ifstream;

namespace ty
{

using line_no = vector<string>::size_type;

class QueryResult;

class TextQuery {
public:
    TextQuery(string&);
    QueryResult query(const string&) const;

private:
    ifstream _is;
    shared_ptr<vector<string>> file;              // store file by lines
    map<string, shared_ptr<set<line_no>>> wm;     // record every words and its line no. set
};
} // end of namespace ty
#endif