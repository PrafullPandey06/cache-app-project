#include "PolicyFactory.h"

#include "LRUEvictionPolicy.h"
#include "FIFOEvictionPolicy.h"

std::unique_ptr<EvictionPolicy> PolicyFactory::createPolicy(const std::string& policyType) {
    if (policyType == "FIFO") {
        // make_unique is a smart pointer to the FIFOEvictionPolicy object
        // and why it's not new FIFOEvictionPolicy()? -> because make_unique is a smart pointer
        // and it will automatically delete the object when it goes out of scope
        return std::make_unique<FIFOEvictionPolicy>();
    }
    else if (policyType == "LRU") {
        return std::make_unique<LRUEvictionPolicy>();
    }
    return nullptr;
}