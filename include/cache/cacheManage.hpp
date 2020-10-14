#ifndef __TY_CACHEMANAGE_H__
#define __TY_CACHEMANAGE_H__

#include "cache.hpp"
#include "../server/thread.hpp"

#include <vector>

using std::vector;

namespace ty
{

class CacheManage {
public:
    CacheManage(int size, int capacity)
    : _cache_vec(vector<Cache*> (size))
    , _capacity(capacity)
    {}

    void init();

    Cache* getCache(int thread_number) {
        return _cache_vec[thread_number];
    }

private:
    int _capacity;
    vector<Cache*> _cache_vec;
};
} // end of namespace ty
#endif