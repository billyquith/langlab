
#include "lang.hpp"
#include <functional>
#include <array>
#include <cassert>

namespace func {


template <typename FT, typename F>
struct Func
{
    Func(F f) { fn_ = f; }

    std::function<FT> fn_;
};


struct Class
{
    void meth() {}
};


void func() {}


void foo()
{
    Func<void(Class&), void(Class::*)()> mw(&Class::meth);
    Func<void(), void(*)()> fw(&func);
}

//struct Args
//{
//    virtual
//};
//
//template <typename... A>
//struct ArgsImpl {
//    typedef std::tuple<A...> params_t;
//    static constexpr int c_nArgs = sizeof...(A);
//    
//    typedef std::array<const std::type_info*, c_nArgs> arg_t;
//    arg_t info;
//    Args() : info({ &typeid(A)... }) {}
//};

template <int N>
struct Args {
    static constexpr int m_nArgs = N;
    
    typedef std::array<const std::type_info*, m_nArgs> arg_t;
    arg_t m_info;
    
    Args(arg_t&& a) : m_info(a) {}
    
    template <typename... A>
    static Args<N> makeArgs() { return Args({ &typeid(A)... }); }
    
    bool operator == (const Args<N>& other) const
    {
        bool r = true;
        for (int i=0; i < m_nArgs; ++i)
            r &= (m_info[i]->hash_code() == other.m_info[i]->hash_code());
        return r;
    }
    
    bool operator != (const Args<N>& other) const { return !(*this == other); }
};


TEST_CASE("params")
{
    Args<2> args1 = Args<2>::makeArgs<int,float>();
    REQUIRE(args1 == args1);

    Args<2> args2 = Args<2>::makeArgs<int,int>();
    REQUIRE(args1 != args2);
    
    Args<2> args3 = Args<2>::makeArgs<int,float*>();
    REQUIRE(args1 != args3);

    Args<2> args4 = Args<2>::makeArgs<int,float>();
    REQUIRE(args4 == args1);
}

} // func

