#include "../../include/cache/cacheManage.hpp"

#include <unistd.h>

#include <sstream>
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::stringstream;

namespace ty
{

void CacheManage::init() {
    loadConfig();
    for(auto& cache: _cache_vec) {
        cache = new Cache(_capacity);
        cache->loadInConfig(_cold_cache);
    }
}

void CacheManage::loadConfig() {
    ifstream ifs("/home/tor1/keywordPrompterForEncyclopediaSearch/config/cache");
    string line, promoted, wd;
    while(getline(ifs, line)) {
        stringstream word(line);
        word >> wd;
        word >> promoted;
        getline(ifs, line);
        promoted += line;
        getline(ifs, line);
        promoted += line;
        _cold_cache[wd] = promoted;
    }
}

void CacheManage::updateCache() {
    cout << "[updating cache...]" << endl;
    unify();
    store();
    updateChildCache();
    cout << "[update finished]" << endl;
}

// private
void CacheManage::unify() {
    for(auto& child_cache: _cache_vec) {
        Cache copy_cahce = *child_cache;
        Node* tmp = copy_cahce.getHead();
        while(tmp->key != "0" && tmp != nullptr) {
            if(_cold_cache.find(tmp->key) == _cold_cache.end()) {
                _cold_cache[tmp->key] = tmp->value;
                _new_data_list.push_back(make_pair(tmp->key, tmp->value));
            }
            tmp = tmp->back;
        }
    }
}

void CacheManage::store() {
    ofstream ofs("/home/tor1/keywordPrompterForEncyclopediaSearch/config/cache");
    for(auto& elem: _cold_cache) {
        ofs << elem.first << " " << elem.second << endl;
    }
    ofs.close();
}

void CacheManage::updateChildCache() {
    for(auto& child_cache: _cache_vec) {
        for(auto& elem: _new_data_list) {
            child_cache->put(elem.first, elem.second);
        }
    }
}
} // end of namespace ty