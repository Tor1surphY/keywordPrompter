#ifndef __TY_BINARYQUERY_H__
#define __TY_BINARYQUERY_H__

#include "queryBase.hpp"
#include "query.hpp"

#include <string>
#include <memory>

using std::string;
using std::shared_ptr;

namespace ty
{

class BinaryQuery
: public QueryBase {
protected:
    BinaryQuery(const Query& l, const Query& r, string s)
    : lhs(l)
    , rhs(r)
    , op_symbol(s) {}

    string rep() const {
        return "(" + lhs.rep() + " " + op_symbol + " " + rhs.rep() + ")"; 
    }

    Query lhs, rhs;
    string op_symbol;
};


class AndQuery 
: public BinaryQuery {
    friend
    Query operator&(const Query& lhs, const Query& rhs) {
        return shared_ptr<QueryBase> (new AndQuery(lhs, rhs));
    }

    AndQuery(const Query& left, const Query& right)
    : BinaryQuery(left, right, "&") {}

    QueryResult eval(const TextQuery&) const;
};


class OrQuery 
: public BinaryQuery {
    friend
    Query operator|(const Query& lhs, const Query& rhs) {
        return shared_ptr<QueryBase> (new OrQuery(lhs, rhs));
    }
    OrQuery(const Query& left, const Query& right)
    : BinaryQuery(left, right, "|") {}

    QueryResult eval(const TextQuery&) const;
};
} // end of namespace ty
#endif