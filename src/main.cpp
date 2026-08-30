/*
======================== STACK vs HEAP ========================

1. Stack Allocation

    Cache cache;

- Memory is allocated on the stack.
- Constructor is called automatically.
- Destructor is called automatically when the object
  goes out of scope.
- Fast allocation/deallocation.
- No manual memory management required.

Example:

    {
        Cache cache;
    } // Destructor automatically called here


2. Heap Allocation

    Cache* cache = new Cache();

- Memory is allocated on the heap.
- Constructor is called automatically.
- Object survives until explicitly deleted.
- Programmer is responsible for cleanup.

Example:

    Cache* cache = new Cache();

    delete cache;   // Destructor called here

- Forgetting delete causes a memory leak.


3. Rule of Thumb

Prefer:

    Cache cache;

Use heap allocation only when:
- Object lifetime must extend beyond current scope.
- Large objects need dynamic lifetime.
- Polymorphism is required (base-class pointers).
- Ownership needs to be shared/transferred.

Modern C++ usually avoids raw new/delete and instead uses:

    std::unique_ptr<Cache>
    std::shared_ptr<Cache>

which automatically manage heap memory.


4. Key Idea

Stack Object:
    Scope Ends  ---> Destructor Called Automatically

Heap Object:
    delete Obj  ---> Destructor Called Automatically

No delete:
    Memory Leak
==============================================================

======================== std::move + std::unique_ptr ========================

RAW POINTER vs UNIQUE_PTR

Raw Pointer:
    T* ptr;

Means:
    - I know where the object is.
    - Ownership is unclear.
    - Who deletes the object? Not obvious.

unique_ptr:
    std::unique_ptr<T> ptr;

Means:
    - I own this object.
    - I am responsible for deleting it.
    - Ownership is explicit.

-----------------------------------------------------------------------

WHY unique_ptr CANNOT BE COPIED

auto policy = std::make_unique<LRUEvictionPolicy>();

If copying were allowed:

    auto anotherPolicy = policy;

Then:

    policy         owns LRUPolicy
    anotherPolicy  owns LRUPolicy

When destructors run:

    delete LRUPolicy
    delete LRUPolicy   <-- Double delete ❌

Therefore unique_ptr is non-copyable.

-----------------------------------------------------------------------

WHAT std::move MEANS

std::move(ptr)

Means:

    "Transfer ownership from one owner to another."

Example:

    auto policy = PolicyFactory::create("LRU");

    Cache cache(
        3,
        std::move(policy));

Before move:

    policy ---> LRUPolicy

After move:

    policy        -> nullptr
    cache.policy  ---> LRUPolicy

Only one owner remains.

-----------------------------------------------------------------------

WHY MOVE TWICE?

1) First move

    Cache cache(
        3,
        std::move(policy));

Ownership:

    main.policy
           ↓
    constructor parameter

2) Second move

    Cache::Cache(
        size_t capacity,
        std::unique_ptr<EvictionPolicy> policy)
        : policy(std::move(policy))
    {
    }

Ownership:

    constructor parameter
                ↓
    Cache::policy member

-----------------------------------------------------------------------

VISUALIZATION

Before:

    main

    policy ---> LRUPolicy

After first move:

    main.policy -> nullptr

    constructor.policy ---> LRUPolicy

After second move:

    constructor.policy -> nullptr

    Cache::policy ---> LRUPolicy

-----------------------------------------------------------------------

BUILDER BUG EXAMPLE

Cache CacheBuilder::build()
{
    auto policy =
        PolicyFactory::create("LRU");

    Cache cache(
        capacity_,
        policy.get());

    return cache;
}

Problem:

    policy owns LRUPolicy.

When build() exits:

    policy is destroyed.
    LRUPolicy is deleted.

But Cache still stores the raw pointer.

Result:

    Cache -> dangling pointer ❌

This is Undefined Behaviour.

-----------------------------------------------------------------------

CORRECT SOLUTION

class Cache
{
private:
    std::unique_ptr<EvictionPolicy> policy;
};

Builder:

    auto policy =
        PolicyFactory::create("LRU");

    Cache cache(
        capacity_,
        std::move(policy));

Ownership transfers safely to Cache.

When Cache dies:

    Cache destructor
          ↓
    unique_ptr destructor
          ↓
    delete LRUPolicy

No leaks.
No dangling pointers.
No manual delete.

-----------------------------------------------------------------------

RULE OF THUMB

T*
    -> knows WHERE the object is.

std::unique_ptr<T>
    -> knows WHERE the object is
       AND
       who OWNS the object.

Whenever ownership is transferred,
use std::move().

=========================================================================
*/


#include "Cache.h"
#include <iostream>
#include "FIFOEvictionPolicy.h"
#include "LRUEvictionPolicy.h"
#include "PolicyFactory.h"
#include "LoggingObserver.h"
#include "MetricObserver.h"
#include "CacheBuilder.h"

int main() {
    // get() is used to get the raw pointer from the smart pointer
    // current polcy is unique_ptr but cache expects a Exception policy pointer
    // Cache cache(3, std::move(policy));
    LoggingObserver observer;
    MetricObserver metricObserver;
    // cache.addObserver(&observer);
    // cache.addObserver(&metricObserver);

    auto cache = CacheBuilder()
                  .capacity(3)
                  .policy("LRU")
                  .addObserver(observer)
                  .addObserver(metricObserver)
                  .Build();

    cache.put("A", 1);
    cache.put("B", 2);
    cache.put("C", 3);
    
    // Initial LRU order: A B C

    std::cout
        << "Getting A: "
        << cache.get("A")
        << '\n';

    // New LRU order: B C A
    // Therefore B should be evicted.
    cache.put("D", 4);

    std::cout << std::boolalpha;

    std::cout
        << "A exists: "
        << cache.exists("A")
        << '\n';

    std::cout
        << "B exists: "
        << cache.exists("B")
        << '\n';

    std::cout
        << "C exists: "
        << cache.exists("C")
        << '\n';

    std::cout
        << "D exists: "
        << cache.exists("D")
        << '\n';

    metricObserver.printMetrics();
    return 0;
}
