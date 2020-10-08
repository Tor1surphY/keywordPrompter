#include "../include/binaryQuery.hpp"

#include <set>
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::set;
using std::make_shared;

using line_no = vector<string>::size_type;

namespace ty
{

QueryResult OrQuery::eval(const TextQuery& text) const {
    auto right = rhs.eval(text),
         left  = lhs.eval(text);
    auto ret_lines = make_shared<set<line_no>> (left.begin(), left.end());
    ret_lines->insert(right.begin(), right.end());
    return QueryResult(rep(), ret_lines, left.getFile());
}

QueryResult AndQuery::eval(const TextQuery& text) const {
    auto left  = lhs.eval(text),
         right = rhs.eval(text);
    auto ret_lines = make_shared<set<line_no>> ();
    set_intersection(left.begin(),   left.end(),
                     right.begin(), right.end(),
                     inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(rep(), ret_lines, left.getFile());
}
} // end of namespace ty