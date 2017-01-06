#include <tests/testDynamicLoader.h>

using namespace std;

#ifdef _WIN32
const string lib1name = "libtestDynamicLoaderLib1.dll";
const string lib2name = "libtestDynamicLoaderLib2.dll";
#endif

const string symbolName = "CreateTestClass";

template <typename Type>
void print(vector<Type> a)
{
    for (auto &i : a)
    {
        cout << i << ' ';
    }
    cout << endl;
}

int main()
{
    vector<int> data = {3, 5, 4, 1, 2, 6, 0};
    cout << "original data:" << endl;
    print(data);

    auto lib1 = DynamicLoader::Load(lib1name);
    EntranceType c1 = lib1->LoadSymbol<EntranceType>(symbolName);
    shared_ptr<testClassBase>t1(c1());
    t1->Data(data);
    auto s1 = t1->sort();
    cout << "sorted by testClass1:" << endl;
    print(s1);

    auto lib2 = DynamicLoader::Load(lib2name);
    auto c2 = lib2->LoadSymbol<EntranceType>(symbolName);
    shared_ptr<testClassBase>t2(c2());
    t2->Data(data);
    auto s2 = t2->sort();
    cout << "sorted by testClass2:" << endl;
    print(s2);
    cout << "Passed!" << endl;
    return 0;
}
