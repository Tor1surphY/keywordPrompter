#include "initConfig.hpp"

#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::istringstream;

namespace ty
{

InitConfig::InitConfig(const string& corpora_dir, const string& dic, const string& idx)
: _corpora_dir(corpora_dir)
, _ofs_dic(dic)
, _ofs_idx(idx){
    if(_ofs_dic.bad()) {
        perror("ofstream");
        exit(1);
    }
    if(_ofs_idx.bad()) {
        perror("ofstream");
        exit(1);
    }
}

InitConfig::~InitConfig() {
    _ofs_dic.close();
    _ofs_idx.close();
}

void InitConfig::generateDic() {
    getFileName();
    int cnt = 0;
    cout << "generating dictionary..." << endl;
    for(auto file : _file_name) {
        file = _corpora_dir + "/" + file;
        writeInDic(file);
        fflush(stdout);
        cout << '\r' << ++cnt << " files";
    }
    cout << endl << "dictionary generated successed." << endl;
}

void InitConfig::getFileName() {
    DIR* dir;
    dir = opendir(_corpora_dir.c_str());
    if(dir == nullptr) {
        perror("opendir");
        exit(1);
    }

    struct dirent* file_ptr;
    while((file_ptr = readdir(dir)) != nullptr) {
        if(string(file_ptr->d_name) == "." || string(file_ptr->d_name) == "..") {
            continue;
        }
        _file_name.push_back(string(file_ptr->d_name));
    }
}

void InitConfig::generateIdx() {
    cout << "generating index..." << endl;
    for(auto& _pair : _alp_frq) {
        char c = _pair.first;
        _ofs_idx << c << "  ";
        for(auto& word : _alp_frq[c]) {
            _ofs_idx << word << " ";
        }
        _ofs_idx << endl;
    }
    cout << "index generated successed." << endl;
}

void InitConfig::writeInDic(string& file) {
    ifstream corpora_file(file);
    if(corpora_file.bad()) {
        perror("ifstream");
        exit(1);
    }
    string line;
    while(getline(corpora_file, line)) {
        string word;
        istringstream iss(line);
        while(iss >> word) {
            if(word.size() <= 2) continue;
            if(
                ('A' <= word[0] && word[0] <= 'Z') ||
                ('a' <= word[0] && word[0] <= 'z')
            ) {
                for(int i = 0; i < word.size(); ++i) {
                    if('A' <= word[i] && word[i] <= 'Z') {
                        word[i] += 32;
                    }
                }
                for(int i = 0; i < word.size(); ++i) {
                    if(('a' <= word[i] && word[i] <= 'z') == 0) {
                        word = word.substr(0, i);
                        break;
                    }
                }
                if(word.size() <= 2) continue;
                ++_word_frq[word];
                _alp_frq[word[0]].insert(word);
            }
        }
    }
    corpora_file.close();
    for(auto& _pair : _word_frq) {
        _ofs_dic << _pair.first << " " << _pair.second << endl;
    }
}
} // end of namespace ty