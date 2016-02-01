#include "PhotoSphereProperty.h"


PhotoSphereProperty *PhotoSphereProperty::FromFile(const string &name)
{
    NULLPTREXAM(SXMPMeta::Initialize(), "XMPMeta initialize failed!", NULLFUNCTION);
    NULLPTREXAM(SXMPFiles::Initialize(), "XMPFiles initialize failed!", NULLFUNCTION);

    SXMPFiles xmp_file;
    SXMPMeta xmp_meta;

    PhotoSphereProperty *ret = new PhotoSphereProperty();
    NULLPTREXAM(ret != nullptr, "Creating class PhotoSphereProperty failed!", XMP_Terminate);

    ret->m_FileName = name;
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

void PhotoSphereProperty::XMP_Terminate()
{
    SXMPFiles::Terminate();
    SXMPMeta::Terminate();
}

PhotoSphereProperty::PhotoSphereProperty()
{
}

PhotoSphereProperty::~PhotoSphereProperty()
{
}


const uint32_t PhotoSphereProperty::m_nProperty = 22;

const string PhotoSphereProperty::m_Namespace = "GPano:";

const XMPProperty PhotoSphereProperty::PhotoSphereProperties[m_nProperty] = {
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
};


