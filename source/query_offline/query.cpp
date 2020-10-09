#include "../../include/query_offline/textQuery.hpp"
#include "../../include/query_offline/queryResult.hpp"

#include <iostream>

using namespace ty;
using std::cin;
using std::cout;
using std::endl;
using std::string;

void query(){
    string path= "/home/tor1/keywordPrompterForEncyclopediaSearch/config/Gutenberg/china_daily.txt";
    TextQuery tq(path);
    string exp;
    while(1){
        cout << "Please input the word/expression that want to search: " << endl;
        cin >> exp;
        QueryResult qr = tq.query(exp);
        print(cout, qr) << endl;
    }
}

int main(){
    query();
    return 0;
}