#include "../../include/cache/cacheManage.hpp"

namespace ty
{

void CacheManage::init() {
    for(auto& cache: _cache_vec) {
        cache = new Cache(_capacity);
    }
}
} // end of namespace ty