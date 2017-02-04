
#include "lang.hpp"

//----------------------------------------------------------------------------

TEST_CASE("Implicit conversion")
{
    SECTION("int-float")
    {
        int i = 7;
        float f = 2.7f;
        
        STATIC_ASSERT(TYPE_IS_SAME(decltype(i), int));
        STATIC_ASSERT(TYPE_IS_SAME(decltype(f), float));
        
        STATIC_ASSERT(TYPE_IS_SAME(decltype(i * f), float));
        STATIC_ASSERT(TYPE_IS_SAME(decltype(i / f), float));
        STATIC_ASSERT(TYPE_IS_SAME(decltype(i + f), float));
        STATIC_ASSERT(TYPE_IS_SAME(decltype(i - f), float));

        STATIC_ASSERT(TYPE_IS_SAME(decltype(f * i), float));
        STATIC_ASSERT(TYPE_IS_SAME(decltype(f / i), float));
        STATIC_ASSERT(TYPE_IS_SAME(decltype(f + i), float));
        STATIC_ASSERT(TYPE_IS_SAME(decltype(f - i), float));
        
        STATIC_ASSERT( ! TYPE_IS_SAME(decltype(i * f), int));
    }
    
    SECTION("float-double")
    {
        float f = 2.7f;
        double d = 8.3;
        
        STATIC_ASSERT(TYPE_IS_SAME(decltype(f), float));
        STATIC_ASSERT(TYPE_IS_SAME(decltype(d), double));
        
        STATIC_ASSERT(TYPE_IS_SAME(decltype(d * f), double));
        STATIC_ASSERT(TYPE_IS_SAME(decltype(d / f), double));
        STATIC_ASSERT(TYPE_IS_SAME(decltype(d + f), double));
        STATIC_ASSERT(TYPE_IS_SAME(decltype(d - f), double));
        
        STATIC_ASSERT(TYPE_IS_SAME(decltype(f * d), double));
        STATIC_ASSERT(TYPE_IS_SAME(decltype(f / d), double));
        STATIC_ASSERT(TYPE_IS_SAME(decltype(f + d), double));
        STATIC_ASSERT(TYPE_IS_SAME(decltype(f - d), double));
        
        STATIC_ASSERT( ! TYPE_IS_SAME(decltype(d * f), float));
    }
}

