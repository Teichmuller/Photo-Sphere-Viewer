#include <Utilities.h>
#include <glm/gtc/matrix_transform.hpp>
#include <ErrorHandler.h>

namespace PhotoSphereViewer
{

    /// spherical format: (phi, theta, radius)
    //vec3 SphericalToCartesian(const vec3 &sp)
    //{
    //    double sv = sin(sp.t), cv = cos(sp.t), sh = sin(sp.s), ch = cos(sp.s);
    //    return vec3(cv * sh, sv, cv * ch) * sp.p;
    //}

    bool GetXMPBoolValue(const Exiv2::XmpData &data, const XMPProperty &property, bool *ret)
    {
        auto value_iter = data.findKey(Exiv2::XmpKey(property.Name));
        COND_ERROR_HANDLE_FALSE(value_iter != data.end(), string("Key ") + property.Name + " doesn't exist!", NOACTION);

        bool v_bool;
        const Exiv2::Xmpdatum &value_b = *value_iter;
        long v_tmp_bool = value_b.toLong();
        COND_ERROR_HANDLE_FALSE(v_tmp_bool != -1, string("Key ") + property.Name + " is not set!", NOACTION);

        v_bool = (v_tmp_bool == 0 ? false : true);
        *ret = v_bool;
        return true;
    }

    bool GetXMPIntValue(const Exiv2::XmpData &data, const XMPProperty &property, long *ret)
    {
        auto value_iter = data.findKey(Exiv2::XmpKey(property.Name));
        COND_ERROR_HANDLE_FALSE(value_iter != data.end(), string("Key ") + property.Name + " doesn't exist!", NOACTION);

        const Exiv2::Xmpdatum &value_b = *value_iter;
        long v_long = value_b.toLong();
    //    COND_ERROR_HANDLE_FALSE(v_long != -1, string("Key ") + property.Name + " is not set!", NOACTION);

        *ret = v_long;
        return true;
    }

    bool GetXMPFloatValue(const Exiv2::XmpData &data, const XMPProperty &property, float *ret)
    {
        auto value_iter = data.findKey(Exiv2::XmpKey(property.Name));
        COND_ERROR_HANDLE_FALSE(value_iter != data.end(), string("Key ") + property.Name + " doesn't exist!", NOACTION);

        const Exiv2::Xmpdatum &value_b = *value_iter;
        float v_float = value_b.toFloat();
    //    COND_ERROR_HANDLE_FALSE(v_float != -1, string("Key ") + property.Name + " is not set!", NOACTION);

        *ret = v_float;
        return true;
    }

    bool GetXMPStringValue(const Exiv2::XmpData &data, const XMPProperty &property, string *ret)
    {
        auto value_iter = data.findKey(Exiv2::XmpKey(property.Name));
        COND_ERROR_HANDLE_FALSE(value_iter != data.end(), string("Key ") + property.Name + " doesn't exist!", NOACTION);

        const Exiv2::Xmpdatum &value_b = *value_iter;
        string v_string = value_b.toString();
    //    COND_ERROR_HANDLE_FALSE(v_string != "", string("Key ") + property.Name + " is not set!", NOACTION);

        *ret = v_string;
        return true;
    }

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
}
