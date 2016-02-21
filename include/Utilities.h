#ifndef __PSV_DEMO_UTILITIES_H__
#define __PSV_DEMO_UTILITIES_H__

#include <iostream>
#include <XMP_config.h>
#include <glm/glm.hpp>


using namespace std;
using namespace glm;


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

//vec3 SphericalToCartesian(const vec3 &sp);
ostream &operator<<(ostream &os, const vec3 &v);
ostream &operator<<(ostream &os, const mat4 &m);
vec3 MatToAngles(mat4 trans);
mat4 AnglesToMat(vec3 angles);


#endif // __UTILITIES_H__
