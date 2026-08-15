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

int main() {
    Cache cache;
    cache.put("age", 26);

    std::cout << cache.get("age") << std::endl;

    std::cout << cache.exists("age") << std::endl;

    cache.remove("age");

    std::cout << cache.exists("age") << std::endl;

    return 0;
}