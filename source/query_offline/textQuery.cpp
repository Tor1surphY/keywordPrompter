#include "../../include/query_offline/textQuery.hpp"
#include "../../include/query_offline/queryResult.hpp"

#include <iostream>
#include <sstream>

using std::endl;
using std::ofstream;
using std::istringstream;

namespace ty
{

TextQuery::TextQuery(string& path)
: _file(new vector<string>)
, _is(path) {
    string text;
    while(getline(_is, text)) {
        _file->push_back(text);
        int n = _file->size()-1;
        istringstream line(text);
        string word;
        while (line >> word) {
            // auto == shared_ptr<set<int>>
            auto& lines = _wm[word];
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
    auto loc = _wm.find(target);
    // if cannot found, return this empty set
    if(loc == _wm.end()) return QueryResult(target, no_data, _file);
    else                return QueryResult(target, loc->second, _file);
}

void TextQuery::generateDictionary() {
    string path = "/home/tor1/keywordPrompterForEncyclopediaSearch/lib/dictionary";
    ofstream ofs(path);
    for(auto& elem : _wm){
        ofs.setf(std::ios::left);
        ofs << "|" ;
        ofs.width(20);
        ofs << elem.first << " ";
        ofs.width(5);
        ofs << elem.second << "|"<< endl;
    }
    ofs.close();
}
} // end of namespace ty