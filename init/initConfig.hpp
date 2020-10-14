#ifndef __TY_INITCONFIG_H__
#define __TY_INITCONFIG_H__

#include <dirent.h>


#include <set>
#include <vector>
#include <fstream>
#include <string>
#include <map>

using std::map;
using std::set;
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;

namespace ty{

class InitConfig {
public:
    InitConfig(const string&, const string&, const string&);
    ~InitConfig();

    void generateDic();
    void generateIdx();

private:
    void getFileName();
    void writeInDic(string&);

private:
    string _corpora_dir;
    vector<string> _file_name;
    ofstream _ofs_dic;
    ofstream _ofs_idx;
    map<string, int> _word_frq;
    map<char, set<string>> _alp_frq;
};
} // end of namespace ty
#endif