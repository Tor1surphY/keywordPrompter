#include "../include/textQuery.hpp"
#include "../include/queryResult.hpp"
#include "../include/query.hpp"

#include <iostream>
#include <sstream>

using std::istringstream;

namespace ty
{

TextQuery::TextQuery(string& path)
: file(new vector<string>)
, _is(path) {
    string text;
    while(getline(_is, text)) {
        file->push_back(text);
        int n = file->size()-1;
        istringstream line(text);
        string word;
        while (line >> word) {
            // auto == shared_ptr<set<int>>
            auto& lines = wm[word];
            // when word not exist, init new set<line_no>
            if(!lines) lines.reset(new set<line_no>);
            lines->insert(n);
        }
    }
}

QueryResult TextQuery::query(const string& target) const {
    // this no_data in case cannot find the target word
    static
    shared_ptr<set<line_no>> no_data(new set<line_no>);
    auto loc = wm.find(target);
    // if cannot found, return this empty set
    if(loc == wm.end()) return QueryResult(target, no_data, file);
    else                return QueryResult(target, loc->second, file);
}

ostream& operator<<(ostream& os, const Query& query) {
    return os << query.rep();
}
} // end of namespace ty