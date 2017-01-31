#ifndef __PHOTOSPHEREVIEWER_UTILITIES_H__
#define __PHOTOSPHEREVIEWER_UTILITIES_H__

#include <iostream>
#include <exiv2/exiv2.hpp>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

namespace PhotoSphereViewer
{
    #define SAFE_DELETE(p) {if ((p) != nullptr) delete (p);}

    enum XMPPropertyType
    {
        Bool,
        Int,
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

    bool GetXMPBoolValue(const Exiv2::XmpData &data, const XMPProperty &property, bool *ret);
    bool GetXMPIntValue(const Exiv2::XmpData &data, const XMPProperty &property, long *ret);
    bool GetXMPFloatValue(const Exiv2::XmpData &data, const XMPProperty &property, float *ret);
    bool GetXMPStringValue(const Exiv2::XmpData &data, const XMPProperty &property, string *ret);

    //vec3 SphericalToCartesian(const vec3 &sp);
    ostream &operator<<(ostream &os, const vec3 &v);
    ostream &operator<<(ostream &os, const mat4 &m);
    vec3 MatToAngles(mat4 trans);
    mat4 AnglesToMat(vec3 angles);
}


#endif // __UTILITIES_H__
