#ifndef __PSV_DEMO_UTILITIES_H__
#define __PSV_DEMO_UTILITIES_H__

#include <iostream>
#include "XMP_config.h"


using namespace std;

#define NOACTIONEXAM(x, msg, final) {if (!(x)) {cout << (msg) << endl;}}
#define GLOBALEXAM(x, msg, final) {if (!(x)) {cout << (msg) << endl; (final)(); exit(1);}}
#define LOCALEXAM(x, msg, final) {if (!(x)) {cout << (msg) << endl; (final)(); return false;}}
#define NULLPTREXAM(x, msg, final) {if (!(x)) {cout << (msg) << endl; (final)(); return nullptr;}}

void NULLFUNCTION();

ostream &operator<<(ostream &os, XMP_DateTime const &d);

enum XMPPropertyType
{
    Bool,
    Int,
    Int64,
    Float,
    Date,
    String
};

struct XMPProperty
{
    string Name;
    XMPPropertyType Type;
    bool IsRequired;
};


#endif // __UTILITIES_H__
