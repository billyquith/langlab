
#include "lang.hpp"



//
//  - http://en.cppreference.com/w/cpp/language/decltype
//  - Related: std::declval<>
//
TEST_CASE("decltype")
{
    struct S { int i; double d; };
    auto l1 = []() -> int { return 0; };
    
    SECTION("entity type")
    {
        SA(type_is_same(int, decltype(S::i)));
        SA(type_is_same(double, decltype(S::d)));

        SA(!type_is_same(int*, decltype(S::i)));
        SA(!type_is_same(int&, decltype(S::i)));
        SA(!type_is_same(int&&, decltype(S::i)));
        
        SA(!type_is_same(int, decltype(l1)));   // type is lambda, return type int
    }

    SECTION("expression")
    {
        // decltype(a) a = 3;   -- error: a undeclared
        auto a = 3;
        decltype(a) b = a + 7;
    }
}

