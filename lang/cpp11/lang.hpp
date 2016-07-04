
#include "catch.hpp"

// static assert
#define SA(T) static_assert(T, #T)

// std::is_same - type same
#define TSAME(A,B) std::is_same<A,B>::value
