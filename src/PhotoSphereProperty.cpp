#include <PhotoSphereViewer/PhotoSphereProperty.h>
#include <cxpl/Core/ErrorHandler.h>

using namespace cxpl;
using namespace PhotoSphereViewer;

#define GET_PHOTO_SPHERE_PROPERTY(type, member, index) CHECK_MSG_RET_NULLPTR(GetXMP##type##Value(xmp,\
        PhotoSphereProperties[index], &(member)) || (!PhotoSphereProperties[index].IsRequired),\
        "Get property[index] failed!")

shared_ptr<PhotoSphereProperty> PhotoSphereProperty::FromFile(const string &name)
{
    Exiv2::Image::AutoPtr image;
    try
    {
        image = Exiv2::ImageFactory::open(name);
    }
    catch (...)
    {
        image = Exiv2::Image::AutoPtr(nullptr);
    }
    CHECK_MSG_RET_NULLPTR(image.get() != nullptr, "Open image failed!");

    image->readMetadata();

    Exiv2::XmpData& xmp = image->xmpData();

    CHECK_MSG_RET_NULLPTR(!xmp.empty(), "XMP data are empty!");

    shared_ptr<PhotoSphereProperty> ret(new PhotoSphereProperty);

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

PhotoSphereProperty::PhotoSphereProperty()
{
}

PhotoSphereProperty::~PhotoSphereProperty()
{
}


const uint32_t PhotoSphereProperty::m_nProperty = 22;

const string PhotoSphereProperty::m_Namespace = "GPano:";

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
