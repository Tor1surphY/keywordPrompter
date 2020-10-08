#ifndef __TY_QUERYBASE_H__
#define __TY_QUERYBASE_H__

#include <string>

namespace ty
{

class QueryResult;
class TextQuery;

class QueryBase {
    /* this is a abstruct base class          */
    /* all query class will derived from here */
    friend
    class Query;

protected:
    virtual
    ~QueryBase() = default;

private:
    virtual
    QueryResult eval(const TextQuery&) const = 0;
    virtual
    std::string rep() const = 0;
};
} // end of namespace ty
#endif