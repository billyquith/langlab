
#include "lang.hpp"

//----------------------------------------------------------------------------

namespace polapply {

template <typename T>
struct PolA {
    static T op(T a, T b) { return a+b; }
};

template <typename T>
struct PolB {
    static T op(T a, T b) { return a-b; }
};


template <typename T, typename P>
struct Class1a
{
    static T apply(T a, T b) { return P::op(a, b); }
};

}

TEST_CASE("policy op")
{
    using namespace polapply;
    
    std::tuple<int, float> t1 = {6, 7.5};
    
    using C1a = Class1a<int, PolA<int>>;
    
    REQUIRE(C1a::apply(5,6) == 11);
}

//----------------------------------------------------------------------------


namespace poldata {
    
    template <typename T>
    struct Op1Policy {
        static T op(T a, T b) { return a+b; }
    };
    
    template <typename T>
    struct AccumPolicy {
        
        struct Data {
            T acc;
        };
        
        Data d;
    };
    
//    template <typename T>
//    struct PolicyData {
//        typename AccumPolicy<T>::Data dacc;
//    };

    template <typename T, template <class> class PolicyData, template <class> class PolicyOp>
    struct Custom
    {
        using Type = Custom<T, PolicyData, PolicyOp>;
        
        typename PolicyData<T>::Data pdata;
        
        Type& apply(T a, T b)
        {
            T v = PolicyOp<T>::op;
            PolicyData<T>::show(v);
            return *this;
        }
        
        T data() { return PolicyData<T>::d.acc; }
    };
    
}


TEST_CASE("tuple")
{
    using namespace poldata;
    
    Custom<float, AccumPolicy, Op1Policy> cust;

    
    
//    REQUIRE(C1a::apply(5,6) == 11);
}

//----------------------------------------------------------------------------

// C FFI

extern "C" void foo();

template <typename F> struct Reg;

template <typename R, typename C, typename... A>
struct Reg<R(C::*)(A...)> {
    typedef R(*CFunc)(C&, A...);
    CFunc func;
};

//template <typename R, typename C, typename... A>
//typename Reg<R(C::*)(A...)>::CFunc Reg<R(C::*)(A...)>::func = nullptr;

class C
{
public:
    int foo(int, float) { return 7; }
};

static int bar(C&, int, float) { return 88; }

TEST_CASE("c ffi")
{
    typedef Reg<decltype(&C::foo)> RegType;
    
    C c;
    RegType rt;
    rt.func = &bar;
    rt.func(c, 4, 5.f);
}



//----------------------------------------------------------------------------


//namespace copy {
//    
//    struct D {};
//    
//    const D& bar()
//    {
//        return D();
//    }
//    
//    const D& conv()
//    {
//        return bar();
//    }
//    
//    void called(const D& d)
//    {
//        
//    }
//    
//    void foo()
//    {
//        called(conv());
//    }
//    
//}


//----------------------------------------------------------------------------

namespace typelist {

    struct Null {}; // sentinel
    
    template <typename T, typename U>
    struct Typelist
    {
        typedef T Head;
        typedef U Tail;
    };

    //----

    template <typename TList, typename T> struct Append;
    
    template <> struct Append<Null, Null> {
        typedef Null result;
    };

    template <typename T>
    struct Append<Null, T> {
        typedef Typelist<T, Null> result;
    };

    template <typename Head, typename Tail>
    struct Append<Null, Typelist<Head, Tail>> {
        typedef Typelist<Head, Tail> result;
    };

    template <typename Head, typename Tail, typename T>
    struct Append<Typelist<Head, Tail>, T> {
        typedef Typelist<Head, typename Append<Tail, T>::result> result;
    };

    //----

    
    typedef std::tuple<int, char*, int, long> foo_t;
    
    template <class T, class Tuple>
    struct Index;
    
    template <class T, class... Types>
    struct Index<T, std::tuple<T, Types...>> {
        static const std::size_t value = 0;
    };

    template <class T, class U, class... Types>
    struct Index<T, std::tuple<U, Types...>> {
        static const std::size_t value = 1 + Index<T, std::tuple<Types...>>::value;
    };
    
    static_assert(Index<int, foo_t>::value == 0, "");
    static_assert(Index<long, foo_t>::value == 3, "");
    static_assert(Index<char*, foo_t>::value == 1, "");
    
}

