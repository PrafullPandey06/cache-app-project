// Why return *this?
// This enables method chaining:

// CacheBuilder()
// .capacity(3)
// .policy("LRU")
// .addObserver(&logger);
// Show more lines
// Each function modifies the builder and returns a reference to itself.

#include "CacheBuilder.h"

#include "PolicyFactory.h"

CacheBuilder& CacheBuilder::capacity(size_t capacity) {
    this->capacity_ = capacity;
    return *this;
}

CacheBuilder& CacheBuilder::policy(const std::string& policyType_) {
    this->policyType_ = policyType_;
    return *this;
}

CacheBuilder& CacheBuilder::addObserver(CacheObserver& observer) {
    observers_.push_back(&observer);
    return *this;
}

Cache CacheBuilder::Build() {
    auto policy = PolicyFactory::createPolicy(policyType_);
    Cache cache(capacity_, std::move(policy));

    for(auto observer : observers_) {
        cache.addObserver(observer);
    }
    return cache;
}