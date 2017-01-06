#include <tests/testDynamicLoader.h>

#include <algorithm>

class testClass2 : public testClassBase
{
public:
    vector<int> sort() override
    {
        vector<int> work(m_buffer);
        greater<int> comp;
        std::sort(work.begin(), work.end(), comp);
        return work;
    }
    ~testClass2() {}
};

extern "C"
{
    testClass2 *CreateTestClass()
    {
        return new testClass2;
    }
}
