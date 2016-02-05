#ifndef __PHOTOSPHEREPROPERTY_H__
#define __PHOTOSPHEREPROPERTY_H__

#include "XMP_config.h"
#include "Utilities.h"

#include <string>

using namespace std;

class PhotoSphereProperty
{
public:
    static PhotoSphereProperty *FromFile(const string &name);
    ~PhotoSphereProperty();
private:
/// Constants
    /// Property Constants
    const static uint32_t m_nProperty;
    const static XMPProperty PhotoSphereProperties[];
    const static string m_Namespace;
/// Variables
    string m_FileName;
    string m_schemaNS;

    bool m_UsePanoramaViewer;
    string m_ProjectionType;

    uint32_t m_CroppedAreaImageWidthPixels;
    uint32_t m_CroppedAreaImageHeightPixels;
    uint32_t m_FullPanoWidthPixels;
    uint32_t m_FullPanoHeightPixels;
    uint32_t m_CroppedAreaLeftPixels;
    uint32_t m_CroppedAreaTopPixels;

    uint32_t m_SourcePhotosCount;
    float m_PoseHeadingDegrees;

    XMP_DateTime FirstPhotoDate;
    XMP_DateTime LastPhotoDate;

    static void XMP_Terminate();
    PhotoSphereProperty();
    friend class PhotoSphere;
};

#define GET_PHOTO_SPHERE_PROPERTY(func_type, type, member, index) COND_ERROR_HANDLE_NULLPTR(xmp_meta.func_type(ret->m_schemaNS.data(), PhotoSphereProperties[index].Name.data(), (type*)&(member), nullptr) || !PhotoSphereProperties[index].IsRequired, "Get property[index] failed!", XMP_Terminate)


#endif // __PHOTOSPHEREPROPERTY_H__
