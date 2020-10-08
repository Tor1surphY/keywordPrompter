#ifndef __TY_QUERY_H__
#define __TY_QUERY_H__

#include "queryBase.hpp"
#include "textQuery.hpp"
#include "queryResult.hpp"
#include "wordQuery.hpp"

#include <memory>

namespace ty
{

class Query {
    /* this is an interface class which is used to manage */
    /* QueryBase's inheritment system                     */
    friend
    Query operator~(const Query&);
    friend
    Query operator|(const Query&, const Query&);
    friend
    Query operator&(const Query&, const Query&);

public:
    Query(const string& s)
    : q(new WordQuery(s)) {}

    QueryResult eval(const TextQuery& t) const {
        return q->eval(t);
    }
    string rep() const { return q->rep(); }

private:
    Query(shared_ptr<QueryBase> query)
    : q(query) {}
    shared_ptr<QueryBase> q;
};
} // end of namespace ty
#endif