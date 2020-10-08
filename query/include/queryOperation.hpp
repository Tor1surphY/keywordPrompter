#ifndef __TY_QUERYOPERATION_H__
#define __TY_QUERYOPERATION_H__

#include "textQuery.hpp"
#include "queryResult.hpp"
#include "query.hpp"

namespace ty
{

class QueryOperation {
    friend class OrQuery;
    friend class AndQuery;
    friend class NotQuery; 
public:
    QueryOperation(string& exp, TextQuery& tq)
    : _exp(exp)
    , _tq(tq) {}

    void classify();

private:
    void andQuery();
    void orQuery();
    void notQuery();
    void normalQuery();

private:
    string& _exp;
    TextQuery& _tq;
};
} // end of namespace ty
#endif