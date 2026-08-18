#include "FIFOEvictionPolicy.h"

void FIFOEvictionPolicy::onPut(const std::string& key) {
    insertionOrder.push_back(key);
}

void FIFOEvictionPolicy::onGet(const std::string& ) {
    // FIFO doesn't care about the key  being accessed.
}

void FIFOEvictionPolicy::onRemove(const std::string& key) {
    insertionOrder.remove(key);
}

std::string FIFOEvictionPolicy::evict() {
    std::string key = insertionOrder.front();
    insertionOrder.pop_front();
    return key;
}