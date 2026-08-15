#pragma once

#include <string>
#include <list>

// Since we have a pure virtual function, this is an abstract class.
// you can't create an instance of this class. same as interface in Java.
class EvictionPolicy {
    public:
      // This is pure virtual function meaning it doesn't have a default implementation and all
      // derived classes must implement it.
      virtual std::string evict(std::list<std::string>& insertionOrder) = 0;

      // Base classes should almost always have a virtual destructor.
      virtual ~EvictionPolicy() = default;
};