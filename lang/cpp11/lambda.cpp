
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


template<typename T, typename = void>
struct IsCallable : std::false_type {};
// Return false if we don't want to include function objects void()
// else return is_function<T>

template<typename T>
struct IsCallable<T,
    typename std::enable_if< std::is_same<decltype(void(&T::operator())), void>::value
                             && !std::is_function<T>::value
                            >::type> : std::true_type
{};


template <typename T, typename U = void>
struct IsLambda
{
    static constexpr bool value = false;
};

template <typename T>
struct IsLambda<T, typename std::enable_if<std::is_class<T>::value>::type>
{
    static constexpr bool value = true;
};


template <typename T, typename U = void>
struct IsFW
{
    static constexpr bool value = false;
};

template <typename T>
struct IsFW<std::function<T>>
{
    static constexpr bool value = true;
};


TEST_CASE("Lambda traits")
{
    SECTION("void(void)")
    {
        auto lmb = [](){};
        typedef FuncTraits<decltype(lmb)> LambdaTraits;
        
        STATIC_ASSERT(TYPE_IS_SAME(LambdaTraits::result_type, void));
        STATIC_ASSERT(LambdaTraits::arity == 0);
    }
    
    SECTION("void(int)")
    {
        auto lmb = std::function<void(int)>(); // [](int) {};
        typedef FuncTraits<decltype(lmb)> LambdaTraits;
        
        STATIC_ASSERT(TYPE_IS_SAME(LambdaTraits::result_type, void));
        STATIC_ASSERT(LambdaTraits::arity == 1);
        STATIC_ASSERT(TYPE_IS_SAME(LambdaTraits::arg<0>::type, int));
    }

    SECTION("const char*(void)")
    {
        auto lmb = []() { return "hello"; };
        typedef FuncTraits<decltype(lmb)> LambdaTraits;
        
        STATIC_ASSERT(TYPE_IS_SAME(LambdaTraits::result_type, const char*));
        STATIC_ASSERT(LambdaTraits::arity == 0);
    }
}

TEST_CASE("Tests")
{
    struct C { void foo(); };
    
    SECTION("is lambda")
    {
        auto lmb = [] (void) {};
        typedef decltype(lmb) lmb_t;

        std::function<int(float&)> fw;
        typedef decltype(fw) fw_t;

        STATIC_ASSERT(!IsFW<lmb_t>::value);
        STATIC_ASSERT( IsFW<fw_t>::value);
        
        STATIC_ASSERT(!IsLambda<void()>::value);
        STATIC_ASSERT(!IsLambda<void(*)()>::value);
        STATIC_ASSERT(!IsLambda<decltype(&C::foo)>::value);
        STATIC_ASSERT(!IsLambda<int(C::*)>::value);
        //STATIC_ASSERT(!IsLambda<C>::value);
    }

    SECTION("is callable")
    {
        auto lmb = [] (void) {};
        typedef decltype(lmb) lmb_t;

        std::function<int(float&)> fw;
        typedef decltype(fw) fw_t;
        
        STATIC_ASSERT( IsCallable<lmb_t>::value);
        STATIC_ASSERT( IsCallable<fw_t>::value);
        
        STATIC_ASSERT(!IsCallable<int(int)>::value);
        STATIC_ASSERT(!IsCallable<void(*)()>::value);
        STATIC_ASSERT(!IsCallable<decltype(&C::foo)>::value);
        STATIC_ASSERT(!IsCallable<int(C::*)>::value);
        
        STATIC_ASSERT( std::is_function<void()>::value);
        STATIC_ASSERT(!std::is_function<lmb_t>::value);
        STATIC_ASSERT(!std::is_function<fw_t>::value);
    }
}

TEST_CASE("Lambda properties")
{
    SECTION("props")
    {
        auto lmb = [] (void) {};
        typedef decltype(lmb) lmb_t;
        
        STATIC_ASSERT(std::is_object<lmb_t>::value);
        STATIC_ASSERT(!std::is_pod<lmb_t>::value);
        STATIC_ASSERT(std::is_class<lmb_t>::value);
    }
}

