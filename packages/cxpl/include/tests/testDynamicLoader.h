#ifndef TESTS_TESTDYNAMICLOADER_H_
#define TESTS_TESTDYNAMICLOADER_H_

#include <cxpl/Core/DynamicLoader.h>

#include <vector>

using namespace std;
using namespace cxpl;

class testClassBase : public HotPlugBase
{
public:
    void Data(const vector<int> data_)
    {
        m_buffer = data_;
    }
    virtual vector<int> sort() = 0;
    virtual ~testClassBase() {}
protected:
    vector<int> m_buffer;
};

extern "C"
{
    using EntranceType = testClassBase*(*)();
}

#endif
