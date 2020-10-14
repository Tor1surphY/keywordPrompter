#include "initConfig.hpp"

using namespace ty;

int main() {
    string config_path = "/home/tor1/keywordPrompterForEncyclopediaSearch/config/init";
    ifstream ifs(config_path);
    if(ifs.bad()) {
        perror("ifstream");
        exit(1);
    }

    string croups;
    string dic;
    string idx;
    
    getline(ifs, croups);
    getline(ifs, dic);
    getline(ifs, idx);

    InitConfig init(croups, dic, idx);
    init.generateDic();
    init.generateIdx();

    return 0;
}