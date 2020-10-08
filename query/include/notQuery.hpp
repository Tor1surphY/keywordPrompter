#ifndef __TY_NOTQUERY_H__
#define __TY_NOTQUERY_H__

#include "query.hpp"
#include "queryBase.hpp"

#include <memory>

using std::shared_ptr;
using std::string;

namespace ty
{

class NotQuery 
: public QueryBase {
    friend
    Query operator~(const Query& q) {
        return shared_ptr<QueryBase> (new NotQuery(q));
    }
    NotQuery(const Query& q)
    : query(q) {}

    string rep() const {
        return "~(" + query.rep() + ")";
    }

    QueryResult eval(const TextQuery&) const;

    Query query;
};
} // end of namespace ty
#endif