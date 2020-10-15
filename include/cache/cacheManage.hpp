#ifndef __TY_CACHEMANAGE_H__
#define __TY_CACHEMANAGE_H__

#include "cache.hpp"
#include "../server/thread.hpp"

#include <vector>
#include <map>
#include <list>

using std::unordered_map;
using std::vector;
using std::list;

namespace ty
{

class CacheManage {
public:
    CacheManage(int size, int capacity)
    : _cache_vec(vector<Cache*> (size))
    , _capacity(capacity)
    {}

    void init();

    Cache* getCache(int thread_number) {    return _cache_vec[thread_number];   }
    void updateCache();

private:
    void unify();
    void store();
    void updateChildCache();

private:
    int _capacity;
    vector<Cache*> _cache_vec;
    unordered_map<string, string> _cold_cache;
    list<pair<string, string>> _new_data_list;
};
} // end of namespace ty
#endif