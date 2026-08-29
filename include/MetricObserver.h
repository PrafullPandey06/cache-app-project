#pragma once

#include "CacheObserver.h"
#include <string>

class MetricObserver : public CacheObserver
{
private:
    int puts = 0;
    int gets = 0;
    int evictions = 0;

public:
    void onPut(const std::string& key) override;
    void onGet(const std::string& key) override;
    void onEvict(const std::string& key) override;

    void printMetrics() const;
};
