
#include "lang.hpp"

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

