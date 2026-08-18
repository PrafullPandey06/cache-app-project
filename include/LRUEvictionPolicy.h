#pragma once

#include "EvictionPolicy.h"
#include <list>
#include <string>

class LRUEvictionPolicy : public EvictionPolicy {
  private:
    // Front: least recently used
    // Back: most recently used
    std::list<std::string> usageOrder;

    void markAsRecentlyUsed(const std::string& key);

  public:
    void onPut(const std::string& key) override;
    
    void onGet(const std::string& key) override;

    void onRemove(const std::string& key) override;

    std::string evict() override;
};