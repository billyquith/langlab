
#include "lang.hpp"



//
//  - http://en.cppreference.com/w/cpp/language/decltype
//
TEST_CASE("decltype")
{
    struct S { int i; double d; };
    
    SECTION("entity type")
    {
        SA(TSAME(int, decltype(S::i)));
    }
}

