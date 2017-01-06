#include <tests/testDynamicLoader.h>

#include <algorithm>

class testClass1 : public testClassBase
{
public:
    vector<int> sort() override
    {
        vector<int> work(m_buffer);
        less<int> comp;
        std::sort(work.begin(), work.end(), comp);
        return work;
    }
    ~testClass1() {}
};

extern "C"
{
    testClass1 *CreateTestClass()
    {
        return new testClass1;
    }
}
