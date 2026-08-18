#pragma once

#include "EvictionPolicy.h"
#include <list>
#include <string>

// FIFOEvictionPolicy IS-A EvictionPolicy.
class FIFOEvictionPolicy : public EvictionPolicy {
   private:
     std::list<std::string> insertionOrder; 
   public:
    void onPut(const std::string& key) override;

    void onGet(const std::string& key) override;

    void onRemove(const std::string& key) override;
    // This is the implementation of the pure virtual function in the base class.
    std::string evict() override;
};