#ifndef __PSV_DEMO_UTILITIES_H__
#define __PSV_DEMO_UTILITIES_H__

#include <iostream>
#include "XMP_config.h"


using namespace std;

#define SAFE_DELETE(p) {if ((p) != nullptr) delete (p);}

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
