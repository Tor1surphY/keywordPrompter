#ifndef __TY_WORDQUERY_H__
#define __TY_WORDQUERY_H__

#include "textQuery.hpp"
#include "queryBase.hpp"
#include "queryResult.hpp"
#include "textQuery.hpp"

#include <string>

namespace ty
{

class WordQuery
: public QueryBase {
    friend
    class Query;
    WordQuery(const std::string& s)
    : query_word(s) {}

    QueryResult eval(const TextQuery& t) const {
        return t.query(query_word);
    }
    std::string rep() const { return query_word; }

    std::string query_word;
};
} // end of namespace ty
#endif