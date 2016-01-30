#ifndef __PHOTOSPHERE_H__
#define __PHOTOSPHERE_H__

#include "XMP_config.h"
#include "utilities.h"

#include <string>
#include <array>
using namespace std;

class PhotoSphere
{
public:
    static PhotoSphere *FromFile(const string &name)
    {
        NULLPTREXAM(SXMPMeta::Initialize(), "XMPMeta initialize failed!", NULLFUNCTION);
        NULLPTREXAM(SXMPFiles::Initialize(), "XMPFiles initialize failed!", NULLFUNCTION);

        SXMPFiles xmp_file;
        SXMPMeta xmp_meta;

        PhotoSphere *ret = new PhotoSphere();
        NULLPTREXAM(ret != nullptr, "Creating photo sphere failed!", XMP_Terminate);

        if (!xmp_file.OpenFile(name, kXMP_UnknownFile, kXMPFiles_OpenForRead | kXMPFiles_OpenUseSmartHandler))
        {
            if (!xmp_file.OpenFile(name, kXMP_UnknownFile, kXMPFiles_OpenForUpdate | kXMPFiles_OpenUsePacketScanning))
            {
                NULLPTREXAM(false, "Cannot open " + name + "!", XMP_Terminate);
            }
        }
        NULLPTREXAM(xmp_file.GetXMP(&xmp_meta), "Getting XMP metadata failed!", XMP_Terminate);
        NULLPTREXAM(xmp_meta.GetNamespaceURI(m_Namespace.data(), &(ret->m_schemaNS)), "Get URI failed!", XMP_Terminate);

        #define GET_PROPERTY(func_type, type, member, index) NULLPTREXAM(xmp_meta.func_type(ret->m_schemaNS.data(), PhotoSphereProperties[index].Name.data(), (type*)&(member), nullptr) || !PhotoSphereProperties[index].IsRequired, "Get property[index] failed!", XMP_Terminate)
        GET_PROPERTY(GetProperty_Bool ,	bool	 	,	ret->m_UsePanoramaViewer           	, 0);
        GET_PROPERTY(GetProperty      ,	string	 	,	ret->m_ProjectionType              	, 1);

        GET_PROPERTY(GetProperty_Int  ,	XMP_Int32	,	ret->m_CroppedAreaImageWidthPixels 	, 2);
        GET_PROPERTY(GetProperty_Int  ,	XMP_Int32	,	ret->m_CroppedAreaImageHeightPixels	, 3);
        GET_PROPERTY(GetProperty_Int  ,	XMP_Int32	,	ret->m_FullPanoWidthPixels         	, 4);
        GET_PROPERTY(GetProperty_Int  ,	XMP_Int32	,	ret->m_FullPanoHeightPixels        	, 5);
        GET_PROPERTY(GetProperty_Int  ,	XMP_Int32	,	ret->m_CroppedAreaLeftPixels       	, 6);
        GET_PROPERTY(GetProperty_Int  ,	XMP_Int32	,	ret->m_CroppedAreaTopPixels        	, 7);

        GET_PROPERTY(GetProperty_Int  ,	XMP_Int32	,	ret->m_SourcePhotosCount           	, 8);
        GET_PROPERTY(GetProperty_Float,	double  	,	ret->m_PoseHeadingDegrees          	, 9);

        GET_PROPERTY(GetProperty_Date ,	XMP_DateTime,	ret->FirstPhotoDate               	, 10);
        GET_PROPERTY(GetProperty_Date ,	XMP_DateTime,	ret->LastPhotoDate               	, 11);
        #undef GET_PROPERTY

        XMP_Terminate();
        return ret;
    }
private:
    const static uint32_t m_nProperty = 22;
    static array<XMPProperty, m_nProperty> PhotoSphereProperties;
    static string m_Namespace;
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

    static void XMP_Terminate()
    {
        SXMPFiles::Terminate();
        SXMPMeta::Terminate();
    }
    PhotoSphere() {}
    ~PhotoSphere() {};
};

string PhotoSphere::m_Namespace = "GPano:";
array<XMPProperty, PhotoSphere::m_nProperty> PhotoSphere::PhotoSphereProperties = {{
    {"GPano:UsePanoramaViewer"				,	Bool	,	false	},
    {"GPano:ProjectionType"					,	String	,	true	},
    {"GPano:CroppedAreaImageWidthPixels"	,	Int		,	true	},
    {"GPano:CroppedAreaImageHeightPixels"	,	Int		,	true	},
    {"GPano:FullPanoWidthPixels"			,	Int		,	true	},
    {"GPano:FullPanoHeightPixels"			,	Int		,	true	},
    {"GPano:CroppedAreaLeftPixels"			,	Int		,	true	},
    {"GPano:CroppedAreaTopPixels"			,	Int		,	true	},
    {"GPano:SourcePhotosCount"				,	Int		,	false	},
    {"GPano:PoseHeadingDegrees"				,	Float	,	false	},
    {"GPano:FirstPhotoDate"					,	Date	,	false	},
    {"GPano:LastPhotoDate"					,	Date	,	false	},

    {"GPano:PosePitchDegrees"				,	Float	,	false	},
    {"GPano:PoseRollDegrees"				,	Float	,	false	},
    {"GPano:InitialViewHeadingDegrees"		,	Int		,	false	},
    {"GPano:InitialViewPitchDegrees"		,	Int		,	false	},
    {"GPano:InitialViewRollDegrees"			,	Int		,	false	},
    {"GPano:InitialHorizontalFOVDegrees"	,	Float	,	false	},
    {"GPano:ExposureLockUsed"				,	Bool	,	false	},
    {"GPano:CaptureSoftware"				,	String	,	false	},
    {"GPano:StitchingSoftware"				,	String	,	false	},
    {"GPano:InitialCameraDolly"				,	Float	,	false	}
}};


#endif // __PHOTOSPHERE_H__
