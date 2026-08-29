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
*/

#include "Cache.h"
#include <iostream>
#include "FIFOEvictionPolicy.h"
#include "LRUEvictionPolicy.h"

int main() {
    LRUEvictionPolicy lru;
    Cache cache(3, &lru);

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

    return 0;
}
