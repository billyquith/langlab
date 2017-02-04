
#include "catch.hpp"
#include <iostream>

#define PRINT(FMT, ...) printf(FMT, ##__VA_ARGS__)

// static assert
#define STATIC_ASSERT(T) static_assert(T, #T)

// std::is_same - type same
#define TYPE_IS_SAME(A,B) std::is_same<A,B>::value
