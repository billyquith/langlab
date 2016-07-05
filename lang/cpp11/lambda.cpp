
#include "lang.hpp"
#include <type_traits>

//template <typename F> struct FuncTraits {};

template <typename T>
struct FuncTraits : public FuncTraits<decltype(&T::operator())> {};
// For generic types, directly use the result of the signature of its 'operator()'

template <typename ClassType, typename ReturnType, typename... Args>
struct FuncTraits<ReturnType(ClassType::*)(Args...) const>
// we specialize for pointers to member function
{
    enum { arity = sizeof...(Args) };
    // arity is the number of arguments.
    
    typedef ReturnType result_type;
    
    template <size_t i>
    struct arg
    {
        typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
        // the i-th argument is equivalent to the i-th tuple element of a tuple
        // composed of those arguments.
    };
};

TEST_CASE("Lambda traits")
{
    SECTION("void(void)")
    {
        auto lmb = [](){};
        typedef FuncTraits<decltype(lmb)> LambdaTraits;
        
        SA(type_is_same(LambdaTraits::result_type, void));
        SA(LambdaTraits::arity == 0);
    }
    
    SECTION("void(int)")
    {
        auto lmb = [](int) {};
        typedef FuncTraits<decltype(lmb)> LambdaTraits;
        
        SA(type_is_same(LambdaTraits::result_type, void));
        SA(LambdaTraits::arity == 1);
        SA(type_is_same(LambdaTraits::arg<0>::type, int));
    }

    SECTION("const char*(void)")
    {
        auto lmb = []() { return "hello"; };
        typedef FuncTraits<decltype(lmb)> LambdaTraits;
        
        SA(type_is_same(LambdaTraits::result_type, const char*));
        SA(LambdaTraits::arity == 0);
    }
}

