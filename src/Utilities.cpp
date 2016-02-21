#include "Utilities.h"
#include <glm/gtc/matrix_transform.hpp>

/// spherical format: (phi, theta, radius)
//vec3 SphericalToCartesian(const vec3 &sp)
//{
//    double sv = sin(sp.t), cv = cos(sp.t), sh = sin(sp.s), ch = cos(sp.s);
//    return vec3(cv * sh, sv, cv * ch) * sp.p;
//}

ostream &operator<<(ostream &os, const vec3 &v)
{
    os << '(' << v.x << ',' << v.y << ',' << v.z << ')';
    return os;
}

ostream &operator<<(ostream &os, const mat4 &m)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            os << m[i][j] << ' ';
        os << endl;
    }
    return os;
}

ostream &operator<<(ostream &os, const XMP_DateTime &d)
{
//    SXMPMeta meta;
//    if (d.hasDate)
//        os << d.year << '-' << d.month << '-' << d.day;
//    if (d.hasTime)
//        os << ' ' << d.hour << ':' << d.minute << ':' << d.second << "." << d.nanoSecond;
//    if (d.hasTimeZone)
//    {
//        switch (d.tzSign)
//        {
//        case kXMP_TimeIsUTC:
//            os << ' ' << "UTC";
//            break;
//        case kXMP_TimeWestOfUTC:
//            os << ' ' << "West" << " (-" << d.tzHour << ':' << d.tzMinute << ')';
//            break;
//        case kXMP_TimeEastOfUTC:
//            os << ' ' << "West" << " (+" << d.tzHour << ':' << d.tzMinute << ')';
//            break;
//        default:;
//        }
//    }
    string str;
    TXMPUtils<string>::ConvertFromDate(d, &str);
    os << str;
    return os;
}

vec3 MatToAngles(mat4 trans)
{
    /// order of y-x-z
    float sin_theta = (trans[1][2] > 1 ? 1 : (trans[1][2] < -1 ? -1 : trans[1][2])), cos_theta = sqrt(1 - sin_theta * sin_theta);
    float sin_phi = -trans[0][2] / cos_theta, cos_phi = trans[2][2] / cos_theta;
    float sin_z = -trans[1][0] / cos_theta, cos_z = trans[1][1] / cos_theta;
    float theta, phi, z;
    phi = acos(cos_phi > 1 ? 1 : (cos_phi < -1 ? -1 : cos_phi));
    if (sin_phi < 0) phi = two_pi<float>() - phi;
    z = acos(cos_z > 1 ? 1 : (cos_z < -1 ? -1 : cos_z));
    if (sin_z < 0) z = two_pi<float>() - z;
    theta = asin(sin_theta);
    return vec3(phi, theta, z);
}

mat4 AnglesToMat(vec3 angles)
{
    mat4 trans(1);
    trans = rotate(trans, angles.t, vec3(1, 0, 0));
    trans = rotate(trans, angles.s, vec3(0, 1, 0));
    return trans;
}
