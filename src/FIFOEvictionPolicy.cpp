#include "FIFOEvictionPolicy.h"

std::string FIFOEvictionPolicy::evict(std::list<std::string>& insertionOrder) {
    std::string key = insertionOrder.front();
    insertionOrder.pop_front();
    return key;
}