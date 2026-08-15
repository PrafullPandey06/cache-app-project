#pragma once

#include "EvictionPolicy.h"

// FIFOEvictionPolicy IS-A EvictionPolicy.
class FIFOEvictionPolicy : public EvictionPolicy {
   public:
    // This is the implementation of the pure virtual function in the base class.
    std::string evict(std::list<std::string>& insertionOrder) override;
};