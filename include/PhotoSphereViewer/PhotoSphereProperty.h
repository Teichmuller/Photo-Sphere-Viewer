#ifndef PHOTOSPHEREVIEWER_PHOTOSPHEREPROPERTY_H_
#define PHOTOSPHEREVIEWER_PHOTOSPHEREPROPERTY_H_

#include <exiv2/exiv2.hpp>
#include <string>
#include <memory>

#include <PhotoSphereViewer/Utilities.h>

using namespace std;

namespace PhotoSphereViewer
{
    class PhotoSphereProperty
    {
    public:
        static shared_ptr<PhotoSphereProperty> FromFile(const string &name);
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

        long m_CroppedAreaImageWidthPixels;
        long m_CroppedAreaImageHeightPixels;
        long m_FullPanoWidthPixels;
        long m_FullPanoHeightPixels;
        long m_CroppedAreaLeftPixels;
        long m_CroppedAreaTopPixels;

        long m_SourcePhotosCount;
        float m_PoseHeadingDegrees;

        string FirstPhotoDate;
        string LastPhotoDate;

//        static void XMP_Terminate();
        PhotoSphereProperty();
        friend class PhotoSphere;
    };
}

#endif // __PHOTOSPHEREPROPERTY_H__
