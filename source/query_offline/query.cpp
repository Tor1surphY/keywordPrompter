#include "../../include/query_offline/textQuery.hpp"
#include "../../include/query_offline/queryImplement.hpp"

#include <iostream>

using namespace ty;
using std::cin;
using std::cout;
using std::endl;
using std::string;

void query(){
    string path = "/home/tor1/keywordPrompterForEncyclopediaSearch/config/textQuery";
    TextQuery* p_text_query = TextQuery::getInstance(path);
    p_text_query->loadData();
    string word;
    while(1) {
        cout << "[input your word: ]" << endl;
        cin >> word;
        QueryImplement query(word, p_text_query);
        cout << query.promote() << endl;
        cout << "-----------------------------------------" << endl;
    }
}

int main(){
    query();
    return 0;
}