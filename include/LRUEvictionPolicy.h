#pragma once

#include "EvictionPolicy.h"
#include <list>
#include <string>
#include <unordered_map>

class LRUEvictionPolicy : public EvictionPolicy {
  private:
    // Front: least recently used
    // Back: most recently used
    std::list<std::string> usageOrder;

    // Each key points to its position in the usageOrder list
    // using iterator to the list iterators are provided by each STL container
    // to get postition of an element in the container
    std::unordered_map<std::string, std::list<std::string>::iterator> positions;

    void markAsRecentlyUsed(const std::string& key);

  public:
    void onPut(const std::string& key) override;
    
    void onGet(const std::string& key) override;

    void onRemove(const std::string& key) override;

    std::string evict() override;
};