#ifndef __TY_QUERYRESULT_H__
#define __TY_QUERYRESULT_H__

#include <memory>
#include <string>
#include <vector>
#include <set>

using std::set;
using std::shared_ptr;
using std::string;
using std::vector;
using std::ostream;

namespace ty
{

using line_no = vector<string>::size_type;

class QueryResult {
    friend 
    ostream& print(ostream&, const QueryResult&);

public:
    QueryResult(string t,
    shared_ptr<set<line_no>> l,
    shared_ptr<vector<string>> f)
    : target(t)
    , lines(l)
    , file(f){}
    
private:
    string target;
    shared_ptr<set<line_no>> lines;
    shared_ptr<vector<string>> file;
};
} // end of namespace ty
#endif