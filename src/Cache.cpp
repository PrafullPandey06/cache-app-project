#include "Cache.h"
#include <iostream>

// Constructor Cache belongs to the Cache class.
Cache::Cache() {
    std::cout<< "Cache Created" << std::endl;
}

Cache::~Cache() {
    std::cout<< "Cache Destroyed" << std::endl;
}

// Put function belongs to the Cache class.
// the class member is accessible directly without using the class name as we are inside the class 
// bcoz of :: (scope resolution operator)
void Cache::put(const std::string& key, int value) {
    data[key] = value;
}

bool Cache::exists(const std::string& key) {
    return data.find(key) != data.end();
}

// Important stl behaviour to understand difference between at and []
// [] -> if the key is not found, it will create a new entry with the key and the value is 0
// at -> if the key is not found, it will throw an exception
int Cache::get(const std::string& key){
    return data.at(key);
}

void Cache::remove(const std::string& key) {
    data.erase(key);
}