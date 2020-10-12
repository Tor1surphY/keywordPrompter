#include "../../include/query_offline/textQuery.hpp"

#include <unistd.h>

#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::istringstream;

namespace ty
{

TextQuery* TextQuery::_p_instance = nullptr;

void TextQuery::loadData() {
    cout << "---------------------------" << endl;
    cout << "loading data..." << endl;

    ifstream _dir(_path);
    string dic_path, idx_path;
    getline(_dir, dic_path);
    getline(_dir, idx_path);
    _dir.close();

    cout << "initializing dictionary..." << endl;
    {
        ifstream dic(dic_path);
        string line, word, frq;
        while(getline(dic, line)) {
            istringstream iss(line);
            iss >> word >> frq;
            ++_dic[word];
        }
        dic.close();
    }

    cout << "initializing index..." << endl;
    {
        ifstream idx(idx_path);
        char alp;
        string line, word;
        while(getline(idx, line)) {
            istringstream iss(line);
            iss >> alp;
            while(iss >> word) {
                _idx[alp].push_back(word);
            }
        }
        idx.close();
    }

    cout << "loading finished" << endl;
    cout << "---------------------------" << endl;
    sleep(1);
    system("clear");
}
} // end of namespace ty