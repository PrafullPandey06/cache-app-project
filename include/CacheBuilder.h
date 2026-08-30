#pragma once

#include <vector>
#include <string>

#include "Cache.h"
#include "CacheObserver.h"

class CacheBuilder {
 private:
   size_t capacity_ = 100;

   std::string policyType_ = "FIFO";

   std::vector<CacheObserver*> observers_;

 public:
  CacheBuilder& capacity(size_t capacity_);
  
  CacheBuilder& policy(const std::string& policyType);

  CacheBuilder& addObserver(CacheObserver& observer);

  Cache Build();
};