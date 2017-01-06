#include <sstream>

#define CURRENT_ERROR_HANDLER StringErrorHandler
#include <cxpl/Core/ErrorHandler.h>
using namespace cxpl;
ostringstream sout;
class StringErrorHandler : public ErrorHandler<decltype(sout)>
{
public:
    static StreamType &GetStream()
    {
        static StreamType &os = sout;
        return os;
    }
};

using namespace std;

namespace test
{
    void testMsg()
    {
        const string msg("1 is devided by 0");
        MSG(msg)
    }
    void testFinal()
    {
        const int a = 1, b = 0;
        MSG_FINAL(a << " is devided by " << b, return;)
    }
    void testCheck()
    {
        const int a = 1, b = 0;
        CHECK_MSG(b != 0, a << " is devided by " << b)
    }
    bool testCheckFinal()
    {
        const int a = 1, b = 0;
        CHECK_MSG_FINAL(b != 0, a << " is devided by " << b, return true;)
        return false;
    }
    int testCheckRet()
    {
        const int a = 1, b = 0;
        CHECK_MSG_RET(b != 0, a << " is devided by " << b, 0)
        return -1;
    }
    bool testCheckRetTrue()
    {
        const int a = 1, b = 0;
        CHECK_MSG_RET_TRUE(b != 0, a << " is devided by " << b)
        return false;
    }
    bool testCheckRetFalse()
    {
        const int a = 1, b = 0;
        CHECK_MSG_RET_FALSE(b != 0, a << " is devided by " << b)
        return true;
    }
    void *testCheckRetNullptr()
    {
        const int a = 1, b = 0;
        CHECK_MSG_RET_NULLPTR(b != 0, a << " is devided by " << b)
        return (void*)1;
    }

    static const string StdMsg("1 is devided by 0\n");
    bool CheckMsg()
    {
        const string str = sout.str();
        size_t pos = str.rfind(':');
        string content = str.substr(pos + 2);
        return (content == StdMsg);
    }
}

int main(int argc, char **argv)
{
    using namespace test;
    bool pass, all_pass = true;
    testMsg();
    pass = CheckMsg();
    all_pass = all_pass && pass;

    testFinal();
    pass = CheckMsg();
    all_pass = all_pass && pass;

    testCheck();
    pass = CheckMsg();
    all_pass = all_pass && pass;

    pass = testCheckFinal();
    all_pass = all_pass && pass;
    pass = CheckMsg();
    all_pass = all_pass && pass;
    //cout << sout.str();

    pass = (testCheckRet() == 0);
    all_pass = all_pass && pass;
    pass = CheckMsg();
    all_pass = all_pass && pass;
    //cout << sout.str();

    pass = testCheckRetTrue();
    all_pass = all_pass && pass;
    pass = CheckMsg();
    all_pass = all_pass && pass;
    //cout << sout.str();

    pass = !testCheckRetFalse();
    all_pass = all_pass && pass;
    pass = CheckMsg();
    all_pass = all_pass && pass;
    //cout << sout.str();

    pass = (testCheckRetNullptr() == nullptr);
    all_pass = all_pass && pass;
    pass = CheckMsg();
    all_pass = all_pass && pass;
    //cout << sout.str();

    if (all_pass)
    {
        cout << "Passed!" << endl;
        return 0;
    }
    else
    {
        cout << "Not passed!" << endl;
        return 1;
    }
}
