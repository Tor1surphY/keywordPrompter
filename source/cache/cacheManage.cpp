#include "../../include/cache/cacheManage.hpp"

#include <unistd.h>

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::ofstream;

namespace ty
{

void CacheManage::init() {
    for(auto& cache: _cache_vec) {
        cache = new Cache(_capacity);
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
    _cold_cache.clear();
    for(auto& child_cache: _cache_vec) {
        Cache copy_cahce = *child_cache;
        Node* tmp = copy_cahce.getHead();
        while(tmp->back->key != "0") {
            if(_cold_cache.find(tmp->key) == _cold_cache.end()) {
                _cold_cache[tmp->key] = tmp->value;
                _new_data_list.push_back(make_pair(tmp->key, tmp->value));
            }
        }
    }
}

void CacheManage::store() {
    ofstream ofs("/home/tor1/keywordPrompterForEncyclopediaSearch/config/cache");
    for(auto& elem: _cold_cache) {
        ofs << elem.first << " " << elem.second;
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