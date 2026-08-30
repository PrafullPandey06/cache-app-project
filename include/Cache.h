/*
==================== Returning Objects + unique_ptr + Move Constructor ====================

Problem:

Cache CacheBuilder::build()
{
    Cache cache(...);

    return cache;
}

At first glance it looks like:

    "Just return the cache object."

But when build() returns, the local variable:

    cache

belongs to the function scope and is about to go out of scope.

The caller needs its own Cache object.

So conceptually the compiler needs to do one of:

    Cache(const Cache&)   // Copy Constructor

or

    Cache(Cache&&)        // Move Constructor

to transfer the local Cache object to the caller.

--------------------------------------------------------------------------------------------

Why Copy Constructor Fails

Cache contains:

    std::unique_ptr<EvictionPolicy> policy;

unique_ptr cannot be copied because that would create:

    Cache1 owns policy
    Cache2 owns policy

Result:

    Double delete ❌

Therefore:

    Cache(const Cache&) = delete;

is effectively enforced by unique_ptr.

--------------------------------------------------------------------------------------------

Why Move Constructor Is Needed

Moving transfers ownership safely:

Before move:

    Cache1.policy ---> LRUPolicy

After move:

    Cache1.policy -> nullptr

    Cache2.policy ---> LRUPolicy

Only one owner exists.

--------------------------------------------------------------------------------------------

Why Did Compilation Fail?

Cache had:

    ~Cache()
    {
        std::cout << "Cache Destroyed" << std::endl;
    }

The moment a user-defined destructor is declared:

    ~Cache();

the compiler becomes conservative and does NOT automatically generate
some move operations.

Result:

    Copy Constructor  -> Deleted (because of unique_ptr)
    Move Constructor  -> Not Generated

Now:

    return cache;

has no valid way to transfer the Cache object.

Compilation fails.

--------------------------------------------------------------------------------------------

Fix

Explicitly allow moving:

    Cache(Cache&&) = default;

    Cache& operator=(Cache&&) = default;

Optionally make copy operations explicit:

    Cache(const Cache&) = delete;

    Cache& operator=(const Cache&) = delete;

Now:

    return cache;

works because Cache can move.

--------------------------------------------------------------------------------------------

Important Clarification

The ownership transfer inside:

    Cache cache(
        3,
        std::move(policy));

worked perfectly.

The compile error is NOT about moving the EvictionPolicy.

The compile error is about moving the Cache object itself when returning
from build().

--------------------------------------------------------------------------------------------

Rule Of Thumb

If a class owns resources via:

    std::unique_ptr
    std::vector
    std::mutex
    file handles
    sockets

and you define a custom destructor:

    ~Class();

think about the Rule Of Five:

    Destructor
    Copy Constructor
    Copy Assignment
    Move Constructor
    Move Assignment

Usually:

    Copy = delete
    Move = default

for ownership-based classes.

============================================================================================
*/

#pragma once // "Even if this header is included multiple times, process it only once."

#include <unordered_map>
#include <string>
#include <list> // list is a doubly linked list
#include "EvictionPolicy.h"
#include "CacheObserver.h"
#include <vector>

class Cache {
    private:
        std::unordered_map<std::string, int> data;

        // size_t -> unsigned integer type that is at least 16 bits in size. but main reason to use size_t is
        // that container like map, set, etc. use size_t to store the size of the container and they return it also.
        // why not int? because int is signed integer type that is at least 16 bits in size.
        size_t capacity;

        // This is a pointer to the eviction policy object.
        // unique_ptr is a smart pointer that automatically deletes the object when it goes out of scope.
        // As Cache owns the policy, so Cache is responsible for deleting the policy. Not Policy.
        // Whoever creates Cache is giving ownership of the policy to Cache.
        std::unique_ptr<EvictionPolicy> policy;

        std::vector<CacheObserver*> observers;

    public:
        Cache(size_t capacity, std::unique_ptr<EvictionPolicy> policy);
        ~Cache();

        Cache(Cache&&) = default;
        Cache& operator=(Cache&&) = default;

        Cache(const Cache&) = delete;
        Cache& operator=(const Cache&) = delete;


    // std:: string -> I need a string. Use the string class that lives inside the std namespace.
    // const -> I will not modify it.
    // & -> I don't want to make a copy.
        void put(const std::string&key, int value);
        int get(const std:: string& key);
        bool exists(const std:: string& key);
        void remove(const std:: string& key);
        void addObserver(CacheObserver* observer);
        void notifyPut(const std::string& key);
        void notifyGet(const std::string& key);
        void notifyEvict(const std::string& key);
        void printCache();
};