#include <PhotoSphereProperty.h>
#include <ErrorHandler.h>

using namespace PhotoSphereViewer;
#define GET_PHOTO_SPHERE_PROPERTY(type, member, index) COND_ERROR_HANDLE_NULLPTR(GetXMP##type##Value(xmp,\
        PhotoSphereProperties[index], &(member)) || (!PhotoSphereProperties[index].IsRequired),\
        "Get property[index] failed!", NOACTION)

shared_ptr<PhotoSphereProperty> PhotoSphereProperty::FromFile(const string &name)
{
    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(name);

    COND_ERROR_HANDLE_NULLPTR(image.get() != 0, "Open image failed!", NOACTION);

    image->readMetadata();

    Exiv2::XmpData& xmp = image->xmpData();

    COND_ERROR_HANDLE_NULLPTR(!xmp.empty(), "XMP data are empty!", NOACTION);

    shared_ptr<PhotoSphereProperty> ret(new PhotoSphereProperty);

    /*
    COND_ERROR_HANDLE_NULLPTR(SXMPMeta::Initialize(), "XMPMeta initialize failed!", NOACTION);
    COND_ERROR_HANDLE_NULLPTR(SXMPFiles::Initialize(), "XMPFiles initialize failed!", SXMPMeta::Terminate);

    SXMPFiles xmp_file;
    SXMPMeta xmp_meta;

    PhotoSphereProperty *ret = new PhotoSphereProperty();
    COND_ERROR_HANDLE_NULLPTR(ret != nullptr, "Creating class PhotoSphereProperty failed!", XMP_Terminate);

    ret->m_FileName = name;
    if (!xmp_file.OpenFile(name, kXMP_UnknownFile, kXMPFiles_OpenForRead | kXMPFiles_OpenUseSmartHandler))
    {
        if (!xmp_file.OpenFile(name, kXMP_UnknownFile, kXMPFiles_OpenForUpdate | kXMPFiles_OpenUsePacketScanning))
        {
            COND_ERROR_HANDLE_NULLPTR(false, "Cannot open " + name + "!", XMP_Terminate);
        }
    }
    COND_ERROR_HANDLE_NULLPTR(xmp_file.GetXMP(&xmp_meta), "Getting XMP metadata failed!", XMP_Terminate);
    COND_ERROR_HANDLE_NULLPTR(xmp_meta.GetNamespaceURI(m_Namespace.data(), &(ret->m_schemaNS)), "Getting URI failed!", XMP_Terminate);

    GET_PHOTO_SPHERE_PROPERTY(GetProperty_Bool ,	bool	 	,	ret->m_UsePanoramaViewer           	, 0);
    GET_PHOTO_SPHERE_PROPERTY(GetProperty      ,	string	 	,	ret->m_ProjectionType              	, 1);

    GET_PHOTO_SPHERE_PROPERTY(GetProperty_Int  ,	XMP_Int32	,	ret->m_CroppedAreaImageWidthPixels 	, 2);
    GET_PHOTO_SPHERE_PROPERTY(GetProperty_Int  ,	XMP_Int32	,	ret->m_CroppedAreaImageHeightPixels	, 3);
    GET_PHOTO_SPHERE_PROPERTY(GetProperty_Int  ,	XMP_Int32	,	ret->m_FullPanoWidthPixels         	, 4);
    GET_PHOTO_SPHERE_PROPERTY(GetProperty_Int  ,	XMP_Int32	,	ret->m_FullPanoHeightPixels        	, 5);
    GET_PHOTO_SPHERE_PROPERTY(GetProperty_Int  ,	XMP_Int32	,	ret->m_CroppedAreaLeftPixels       	, 6);
    GET_PHOTO_SPHERE_PROPERTY(GetProperty_Int  ,	XMP_Int32	,	ret->m_CroppedAreaTopPixels        	, 7);

    GET_PHOTO_SPHERE_PROPERTY(GetProperty_Int  ,	XMP_Int32	,	ret->m_SourcePhotosCount           	, 8);
    GET_PHOTO_SPHERE_PROPERTY(GetProperty_Float,	double  	,	ret->m_PoseHeadingDegrees          	, 9);

    GET_PHOTO_SPHERE_PROPERTY(GetProperty_Date ,	XMP_DateTime,	ret->FirstPhotoDate               	, 10);
    GET_PHOTO_SPHERE_PROPERTY(GetProperty_Date ,	XMP_DateTime,	ret->LastPhotoDate               	, 11);

    XMP_Terminate();*/

    GET_PHOTO_SPHERE_PROPERTY(Bool	 	,	ret->m_UsePanoramaViewer           	, 0);
    GET_PHOTO_SPHERE_PROPERTY(String	,	ret->m_ProjectionType              	, 1);

    GET_PHOTO_SPHERE_PROPERTY(Int	    ,	ret->m_CroppedAreaImageWidthPixels 	, 2);
    GET_PHOTO_SPHERE_PROPERTY(Int	    ,	ret->m_CroppedAreaImageHeightPixels	, 3);
    GET_PHOTO_SPHERE_PROPERTY(Int   	,	ret->m_FullPanoWidthPixels         	, 4);
    GET_PHOTO_SPHERE_PROPERTY(Int	    ,	ret->m_FullPanoHeightPixels        	, 5);
    GET_PHOTO_SPHERE_PROPERTY(Int   	,	ret->m_CroppedAreaLeftPixels       	, 6);
    GET_PHOTO_SPHERE_PROPERTY(Int	    ,	ret->m_CroppedAreaTopPixels        	, 7);

    GET_PHOTO_SPHERE_PROPERTY(Int   	,	ret->m_SourcePhotosCount           	, 8);
    GET_PHOTO_SPHERE_PROPERTY(Float  	,	ret->m_PoseHeadingDegrees          	, 9);

    GET_PHOTO_SPHERE_PROPERTY(String    ,	ret->FirstPhotoDate               	, 10);
    GET_PHOTO_SPHERE_PROPERTY(String    ,	ret->LastPhotoDate               	, 11);

    return ret;
}

//void PhotoSphereProperty::XMP_Terminate()
//{
//    SXMPFiles::Terminate();
//    SXMPMeta::Terminate();
//}

PhotoSphereProperty::PhotoSphereProperty()
{
}

PhotoSphereProperty::~PhotoSphereProperty()
{
}


const uint32_t PhotoSphereProperty::m_nProperty = 22;

const string PhotoSphereProperty::m_Namespace = "GPano:";
/*
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
};*/


const XMPProperty PhotoSphereProperty::PhotoSphereProperties[m_nProperty] = {
    {"Xmp.GPano.UsePanoramaViewer"				,	Bool	,	false	},
    {"Xmp.GPano.ProjectionType"					,	String	,	true	},
    {"Xmp.GPano.CroppedAreaImageWidthPixels"	,	Int		,	true	},
    {"Xmp.GPano.CroppedAreaImageHeightPixels"	,	Int		,	true	},
    {"Xmp.GPano.FullPanoWidthPixels"			,	Int		,	true	},
    {"Xmp.GPano.FullPanoHeightPixels"			,	Int		,	true	},
    {"Xmp.GPano.CroppedAreaLeftPixels"			,	Int		,	true	},
    {"Xmp.GPano.CroppedAreaTopPixels"			,	Int		,	true	},
    {"Xmp.GPano.SourcePhotosCount"				,	Int		,	false	},
    {"Xmp.GPano.PoseHeadingDegrees"				,	Float	,	false	},
    {"Xmp.GPano.FirstPhotoDate"					,	Date	,	false	},
    {"Xmp.GPano.LastPhotoDate"					,	Date	,	false	},

    {"Xmp.GPano.PosePitchDegrees"				,	Float	,	false	},
    {"Xmp.GPano.PoseRollDegrees"				,	Float	,	false	},
    {"Xmp.GPano.InitialViewHeadingDegrees"		,	Int		,	false	},
    {"Xmp.GPano.InitialViewPitchDegrees"		,	Int		,	false	},
    {"Xmp.GPano.InitialViewRollDegrees"			,	Int		,	false	},
    {"Xmp.GPano.InitialHorizontalFOVDegrees"	,	Float	,	false	},
    {"Xmp.GPano.ExposureLockUsed"				,	Bool	,	false	},
    {"Xmp.GPano.CaptureSoftware"				,	String	,	false	},
    {"Xmp.GPano.StitchingSoftware"				,	String	,	false	},
    {"Xmp.GPano.InitialCameraDolly"				,	Float	,	false	}
};
