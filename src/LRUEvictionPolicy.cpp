#include "LRUEvictionPolicy.h"
#include <stdexcept>
#include <iterator>

void LRUEvictionPolicy::markAsRecentlyUsed(const std::string& key) {
   auto position = positions.find(key);
   
   // If the key is not found, throw an exception
   if (position == positions.end()) {
    return;
   }

   // If the key is found, remove it from the list and add it to the back.
   // Destination: end of usageOrder
   // Source:      usageOrder itself
   // Node:        node pointed to by positions["A"]
   usageOrder.splice(usageOrder.end(), usageOrder, position->second);

   // The  iterator remains valid after splice operation but assigning it again make the extended
   // mapping explicit.
   positions[key] = std::prev(usageOrder.end());
}

void LRUEvictionPolicy::onPut(const std::string& key)  {
    auto position = positions.find(key);
    // If the key is found, mark it as recently used
    if (position != positions.end()) {
        markAsRecentlyUsed(key);
        return;
    }
    // If the key is not found, add it to the back of the list and update the position map
    usageOrder.push_back(key);
    positions[key] = std::prev(usageOrder.end());
}

void LRUEvictionPolicy::onGet(const std::string& key) {
    auto position = positions.find(key);
    if (position != positions.end()) {
        markAsRecentlyUsed(key);
        return;
    }
    return;
}

void LRUEvictionPolicy::onRemove(const std::string& key) {
    auto position = positions.find(key);
    // If the key is found, remove it from the list and update the position map
    if (position != positions.end()) {
        usageOrder.erase(position->second);
        positions.erase(key);
        return;
    }
    return;
}

std::string LRUEvictionPolicy::evict() {
    // If the list is empty, throw an exception
    if (usageOrder.empty()) {
        throw std::runtime_error("No key to evict");
    }
   
    std::string key = usageOrder.front();
    usageOrder.pop_front();
    positions.erase(key);

    return key;
}