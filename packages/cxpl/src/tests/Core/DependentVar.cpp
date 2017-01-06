#include <cxpl/Core/DependentVar.h>
#include <cxpl/Core/ErrorHandler.h>
#include <iostream>

using namespace std;
using namespace cxpl;

int main(int argc, char **argv)
{
    bool IsPassed = true;
    IInt a(2), b(5);
    DInt c([&](){return a * b;}, {a, b});
    IInt d(-2);
    DInt e([&](){return c + d;}, {c, d});
    DInt f([&](){return a - c;}, {a, c});

    auto printAll = [&]()
    {
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        cout << "c = " << c << endl;
        cout << "d = " << d << endl;
        cout << "e = " << e << endl;
        cout << "f = " << f << endl;
    };
    auto assertAll = [&](int a_, int b_, int c_, int d_, int e_, int f_)
    {
        CHECK_MSG_FINAL(a == a_, "Assert a failed!", IsPassed = false;)
        CHECK_MSG_FINAL(b == b_, "Assert b failed!", IsPassed = false;)
        CHECK_MSG_FINAL(c == c_, "Assert c failed!", IsPassed = false;)
        CHECK_MSG_FINAL(d == d_, "Assert d failed!", IsPassed = false;)
        CHECK_MSG_FINAL(e == e_, "Assert e failed!", IsPassed = false;)
        CHECK_MSG_FINAL(f == f_, "Assert f failed!", IsPassed = false;)
    };

    cout << "Initialized" << endl;
    assertAll(2, 5, 10, -2, 8, -8);
    printAll();
    d = -3;
    cout << "Change d from -2 to -3" << endl;
    assertAll(2, 5, 10, -3, 7, -8);
    printAll();
    a = 3;
    cout << "Change a from 2 to 3" << endl;
    assertAll(3, 5, 15, -3, 12, -12);
    printAll();

//    auto g = make_shared<IInt>(9);
//    DInt h([&](){return (*g) * 2;}, {*g});
//    *g = 8;
//    g = nullptr;
//    cout << "I want you CRASH!!! >> h = " << h <<  endl;

    if (IsPassed) cout << "Passed!" << endl;
    else cout << "Failed!" << endl;
    return 0;
}
