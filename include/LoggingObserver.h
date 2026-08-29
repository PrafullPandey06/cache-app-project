#pragma once

#include "CacheObserver.h"
#include <string>

class LoggingObserver : public CacheObserver {
    public:
      void onPut(const std::string& key) override;
      void onGet(const std::string& key) override;
      void onEvict(const std::string& key) override;
};