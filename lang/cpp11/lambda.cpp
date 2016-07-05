
#include "lang.hpp"
#include <type_traits>

// See http://stackoverflow.com/a/7943765

template <typename T>
struct FuncTraits : public FuncTraits<decltype(&T::operator())>
{};
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


template <typename T, typename U = void>
struct IsLambda {
    static constexpr bool value = false;
};

template <typename T>
struct IsLambda<T, typename std::enable_if<std::is_class<T>::value>::type>
{
    static constexpr bool value = true;
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

TEST_CASE("Is Lambda?")
{
    struct C { void foo(); };
    
    SECTION("test")
    {
        auto lmb = [] (void) {};
        typedef decltype(lmb) lmb_t;
        
        SA(IsLambda<lmb_t>::value);
        
        SA(!IsLambda<void()>::value);
        SA(!IsLambda<void(*)()>::value);        
        SA(!IsLambda<decltype(&C::foo)>::value);
        SA(!IsLambda<int(C::*)>::value);
    }
}

TEST_CASE("Lambda properties")
{
    SECTION("props")
    {
        auto lmb = [] (void) {};
        typedef decltype(lmb) lmb_t;
        
        SA(std::is_object<lmb_t>::value);
        SA(!std::is_pod<lmb_t>::value);
        SA(std::is_class<lmb_t>::value);
    }
}

