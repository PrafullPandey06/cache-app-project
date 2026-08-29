#pragma once

#include <memory>
#include <string>

#include "EvictionPolicy.h"

class PolicyFactory {
    public:
     // static function -> can be called without creating an instance of the class
     // unique_ptr -> smart pointer to the eviction policy object
     // const std::string& policyType -> policy type is a string
     // and why is it static? -> because we want to create the policy object without creating an instance of the class
     static std::unique_ptr<EvictionPolicy> createPolicy(const std::string& policyType);
};