
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
        STATIC_ASSERT(TYPE_IS_SAME(int, decltype(S::i)));
        STATIC_ASSERT(TYPE_IS_SAME(double, decltype(S::d)));

        STATIC_ASSERT(!TYPE_IS_SAME(int*, decltype(S::i)));
        STATIC_ASSERT(!TYPE_IS_SAME(int&, decltype(S::i)));
        STATIC_ASSERT(!TYPE_IS_SAME(int&&, decltype(S::i)));
        
        STATIC_ASSERT(!TYPE_IS_SAME(int, decltype(l1)));   // type is lambda, return type int
    }

    SECTION("expression")
    {
        // decltype(a) a = 3;   -- error: a undeclared
        auto a = 3;
        decltype(a) b = a + 7;
    }
}




//
// Converts type to reference to we can access members.
//
//  - http://en.cppreference.com/w/cpp/utility/declval
//
TEST_CASE("std::declval")
{
    // has default constructor
    struct Default
    {
        int foo() const { return 1; }
    };
    
    // no default constructor
    struct NoDefault
    {
        NoDefault(const NoDefault&) {}
        int foo() const { return 1; }
    };
    
    SECTION("declval")
    {
        decltype(Default().foo()) f1 = 1;                   // type of n1 is int
        
        //  decltype(NonDefault().foo()) f2 = f1;           // error: no default constructor
        
        decltype(std::declval<NoDefault>().foo()) f2 = f1;  // type of n2 is int
    }
}



