#pragma once // "Even if this header is included multiple times, process it only once."

#include <unordered_map>
#include <string>

class Cache {
    private:
        std::unordered_map<std::string, int> data;

    public:
        Cache();
        ~Cache();

    // std:: string -> I need a string. Use the string class that lives inside the std namespace.
    // const -> I will not modify it.
    // & -> I don't want to make a copy.
        void put(const std::string&key, int value);
        int get(const std:: string& key);
        bool exists(const std:: string& key);
        void remove(const std:: string& key);

};