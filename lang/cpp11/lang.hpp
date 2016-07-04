
#include "catch.hpp"
#include <iostream>

#define PRINT(FMT, ...) printf(FMT, ##__VA_ARGS__)

// static assert
#define SA(T) static_assert(T, #T)

// std::is_same - type same
#define type_is_same(A,B) std::is_same<A,B>::value
