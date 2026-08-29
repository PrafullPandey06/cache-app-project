#include "LoggingObserver.h"
#include <iostream>

void LoggingObserver::onPut(const std::string& key) {
    std::cout <<"[LOG] Put key: " << key << std::endl;
}

void LoggingObserver::onGet(const std::string& key) {
    std::cout <<"[LOG] Get key: " << key << std::endl;
}

void LoggingObserver::onEvict(const std::string& key) {
    std::cout <<"[LOG] Evict key: " << key << std::endl;
}