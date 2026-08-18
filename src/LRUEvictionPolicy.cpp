#include "LRUEvictionPolicy.h"

void LRUEvictionPolicy::markAsRecentlyUsed(const std::string& key) {
    usageOrder.remove(key);
    usageOrder.push_back(key);
}

void LRUEvictionPolicy::onPut(const std::string& key)  {
    markAsRecentlyUsed(key);
}

void LRUEvictionPolicy::onGet(const std::string& key) {
    markAsRecentlyUsed(key);
}

void LRUEvictionPolicy::onRemove(const std::string& key) {
    usageOrder.remove(key);
}

std::string LRUEvictionPolicy::evict() {
    std::string key = usageOrder.front();
    usageOrder.pop_front();
    return key;
}