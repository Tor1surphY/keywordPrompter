#ifndef __TY_QUERYIMPLEMENT_H__
#define __TY_QUERYIMPLEMENT_H__

#include "textQuery.hpp"

#include <string>

using std::string;

namespace ty
{

class QueryImplement {
public:
    QueryImplement(const string& word, TextQuery* p_text_query)
    : _word(word)
    , _p_text_query(p_text_query) {}

    string promote();

private:
    int shortestEditDistance(string&, string&);

private:
    string _word;
    TextQuery* _p_text_query;
};
} // end of namespace ty
#endif