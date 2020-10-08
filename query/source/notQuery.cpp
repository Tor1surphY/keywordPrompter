#include "../include/notQuery.hpp"

#include <iostream>

using std::cout;
using std::endl;
using std::make_shared;

namespace ty
{

QueryResult NotQuery::eval(const TextQuery& text) const {
    auto result = query.eval(text);
    auto ret_lines = make_shared<set<line_no>> ();
    auto beg = result.begin(), end = result.end();
    auto sz = result.getFile()->size();
    for (size_t n = 0; n != sz; ++n) {
        if      (beg == end || *beg != n) ret_lines->insert(n);
        else if (beg != end)             ++beg;
    }
    return QueryResult(rep(), ret_lines, result.getFile());
}
} // end of namespace ty