#include "../include/queryOperation.hpp"

#include <iostream>

using std::cout;
using std::endl;

namespace ty
{

void QueryOperation::classify() {
    int flag = 0;
    for (auto word : _exp) {
        if      (word == '~') {
            notQuery();
            flag = 1;
        }
        else if (word == '&') {
            andQuery();
            flag = 2;
        }
        else if (word == '|') {
            orQuery();
            flag = 3;
        }
    }
    if (flag == 0) normalQuery();
}

void QueryOperation::andQuery() {
    string left = "", right = "";
    int tag = 0;
    for (auto cha : _exp) {
        if (cha == '&') {
            tag = 1;
            continue;
        }
        if (tag != 1)   left = cha;
        if (tag == 1)   right = cha;
    }
    Query q = Query(left) & Query(right);
    QueryResult qr = q.eval(_tq);
    print(cout, qr) << endl;
}

void QueryOperation::orQuery() {
    string left = "", right = "";
    int tag = 0;
    for (auto cha : _exp) {
        if (cha == '|') {
            tag = 1;
            continue;
        }
        if (tag != 1)   left += cha;
        if (tag == 1)   right += cha;
    }
    Query q = Query(left) | Query(right);
    QueryResult qr = q.eval(_tq);
    print(cout, qr) << endl;
}


void QueryOperation::notQuery() {
    _exp.erase(_exp.begin());
    Query q = ~Query(_exp);
    QueryResult qr = q.eval(_tq);
    print(cout, qr) << endl;
}

void QueryOperation::normalQuery() {
    Query q = Query(_exp);
    QueryResult qr = q.eval(_tq);
    print(cout, qr) << endl;
}
} // end of namespace ty