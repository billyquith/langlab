
#include "lang.hpp"


class NoEq {};

class Eq {
public:
    bool operator== (const Eq&) { return true; }
};

class ExEq {};
bool operator== (const ExEq&, const ExEq&) { return true; }


// Source: http://stackoverflow.com/a/6536204/3233
namespace TestEq
{
    struct No {};
    template<typename T, typename Arg> No operator== (const T&, const Arg&);
    
    template<typename T, typename Arg = T>
    struct EqualExists
    {
        static constexpr bool value = !std::is_same<decltype(*(T*)(0) == *(Arg*)(0)), No>::value;
    };
}

TEST_CASE("Test for existence of an operator")
{
    
    SECTION("")
    {
        SA(TestEq::EqualExists<NoEq>::value == false);
        SA(TestEq::EqualExists<Eq>::value == true);
        SA(TestEq::EqualExists<ExEq>::value == true);
    }
}

