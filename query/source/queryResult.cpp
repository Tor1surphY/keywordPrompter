#include "../include/queryResult.hpp"
#include "../include/textQuery.hpp"

#include <iostream>

using std::endl;

namespace ty
{

// friend
ostream& print(ostream& os, const QueryResult& qr) {
    os << qr.target << " occurs " 
       << qr.lines->size() << " times" << endl;
    for(auto no : *qr.lines){
        os << "\t(line " << no+1 << ") "
           << *(qr.file->begin()+no) << endl;
    }
    return os;
}
} // end of namespace ty