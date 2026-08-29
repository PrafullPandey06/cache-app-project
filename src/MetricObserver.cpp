#include "MetricObserver.h"
#include <iostream>
#include <string>

void MetricObserver::onPut(const std::string&) {
    puts++;
}

void MetricObserver::onGet(const std::string&) {
    gets++;
}

void MetricObserver::onEvict(const std::string&) {
    evictions++;
}

void MetricObserver::printMetrics() const
{
    std::cout << "\n===== Cache Metrics =====\n";
    std::cout << "Puts      : " << puts << std::endl;
    std::cout << "Gets      : " << gets << std::endl;
    std::cout << "Evictions : " << evictions << std::endl;
}