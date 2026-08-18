#pragma once // "Even if this header is included multiple times, process it only once."

#include <unordered_map>
#include <string>
#include <list> // list is a doubly linked list
#include "EvictionPolicy.h"

class Cache {
    private:
        std::unordered_map<std::string, int> data;

        // size_t -> unsigned integer type that is at least 16 bits in size. but main reason to use size_t is
        // that container like map, set, etc. use size_t to store the size of the container and they return it also.
        // why not int? because int is signed integer type that is at least 16 bits in size.
        size_t capacity;

        // This is a pointer to the eviction policy object.
        EvictionPolicy* policy;

    public:
        Cache(size_t capacity, EvictionPolicy* policy);
        ~Cache();

    // std:: string -> I need a string. Use the string class that lives inside the std namespace.
    // const -> I will not modify it.
    // & -> I don't want to make a copy.
        void put(const std::string&key, int value);
        int get(const std:: string& key);
        bool exists(const std:: string& key);
        void remove(const std:: string& key);
        void printCache();
};