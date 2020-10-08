#include "../include/textQuery.hpp"
#include "../include/queryOperation.hpp"

#include <iostream>
#include <fstream>

using namespace std;
using namespace ty;

void text(){
    string path = "/home/tor1/keywordPrompterForEncyclopediaSearch/config/china_daily.txt";
    TextQuery tq(path);
    string exp;
    while(1){
        cout << "Please input the word/expression that want to search: " << endl;
        cout << "(input q to exit query)" << endl;
        cin >> exp;
        if(exp == "q") break;
        QueryOperation qo(exp, tq);
        qo.classify();
    }
}

int main(){
    text();
    return 0;
}