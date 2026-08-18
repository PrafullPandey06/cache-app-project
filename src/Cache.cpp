#include "Cache.h"
#include <iostream>

/**
Initializer List = How an object/member is CREATED

this-> = How an already-created object is ACCESSED
*/

// Constructor Cache belongs to the Cache class.
// capacity(capacity) -> initialize the capacity member variable with the value of the capacity parameter
// this is same as writitng: this->capacity = capacity;
Cache::Cache(size_t capacity, EvictionPolicy* policy) : capacity(capacity), policy(policy) {
    std::cout<< "Cache Created with this capacity: " << capacity << std::endl;
}

Cache::~Cache() {
    std::cout<< "Cache Destroyed" << std::endl;
}

// Put function belongs to the Cache class.
// the class member is accessible directly without using the class name as we are inside the class 
// bcoz of :: (scope resolution operator)
void Cache::put(const std::string& key, int value) {
    // If the key is already present, update the value and move it to the end of the list
    if(data.find(key) != data.end()) {
        data.at(key) = value;
        policy->onGet(key);
    }
    // If the cache is full, remove the oldest entry
    else if(data.size() >= capacity) {
        // Remove the oldest entry from the list and map
        // policy is a pointer to the eviction policy object.
        // ptr -> function() means (*ptr).function()
        std::string keyToEvict = policy->evict();
        data.erase(keyToEvict);
        std::cout << "Evicting key: " << keyToEvict << std::endl;

        data[key] = value;
        policy->onPut(key);
    } 
    else {
        data[key] = value;
        policy->onPut(key);
    }
}

bool Cache::exists(const std::string& key) {
    return data.find(key) != data.end();
}

// Important stl behaviour to understand difference between at and []
// [] -> if the key is not found, it will create a new entry with the key and the value is 0
// at -> if the key is not found, it will throw an exception
int Cache::get(const std::string& key){
    policy->onGet(key);
    return data.at(key);
}

void Cache::remove(const std::string& key) {
    data.erase(key);
    policy->onRemove(key);
}

// Print the cache in the order of insertion
void Cache::printCache() {
    for(const auto& entry: data) {
        std::cout << entry.first << " : " << entry.second << std::endl;
    }
}