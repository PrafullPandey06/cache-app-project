#pragma once

#include <string>

class CacheObserver {
    public:
      virtual void onPut(const std::string& key) = 0;
      virtual void onGet(const std::string& key) = 0 ;
      virtual void onEvict(const std::string& key) = 0;

      virtual ~CacheObserver() = default;
};