#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include <iostream>
#include <XMP.hpp>

using namespace std;

#define NOACTIONEXAM(x, msg, final) {if (!(x)) {cout << (msg) << endl;}}
#define LOCALEXAM(x, msg, final) {if (!(x)) {cout << (msg) << endl; (final)(); return false;}}
#define GLOBALEXAM(x, msg, final) {if (!(x)) {cout << (msg) << endl; (final)(); exit(1);}}

void NULLFUNCTION() {}

std::ostream &operator<<(std::ostream &os, XMP_DateTime const &d) {
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

string PhotoSphereURI("http://ns.google.com/photos/1.0/panorama/");
vector<XMPProperty> PhotoSphereProperties{
{"GPano:UsePanoramaViewer"				,	Bool	,	false	},
{"GPano:CaptureSoftware"				,	String	,	false	},
{"GPano:StitchingSoftware"				,	String	,	false	},
{"GPano:ProjectionType"					,	String	,	true	},
{"GPano:PoseHeadingDegrees"				,	Float	,	false	},
{"GPano:PosePitchDegrees"				,	Float	,	false	},
{"GPano:PoseRollDegrees"				,	Float	,	false	},
{"GPano:InitialViewHeadingDegrees"		,	Int		,	false	},
{"GPano:InitialViewPitchDegrees"		,	Int		,	false	},
{"GPano:InitialViewRollDegrees"			,	Int		,	false	},
{"GPano:InitialHorizontalFOVDegrees"	,	Float	,	false	},
{"GPano:FirstPhotoDate"					,	Date	,	false	},
{"GPano:LastPhotoDate"					,	Date	,	false	},
{"GPano:SourcePhotosCount"				,	Int		,	false	},
{"GPano:ExposureLockUsed"				,	Bool	,	false	},
{"GPano:CroppedAreaImageWidthPixels"	,	Int		,	true	},
{"GPano:CroppedAreaImageHeightPixels"	,	Int		,	true	},
{"GPano:FullPanoWidthPixels"			,	Int		,	true	},
{"GPano:FullPanoHeightPixels"			,	Int		,	true	},
{"GPano:CroppedAreaLeftPixels"			,	Int		,	true	},
{"GPano:CroppedAreaTopPixels"			,	Int		,	true	},
{"GPano:InitialCameraDolly"				,	Float	,	false	}
};

#endif // __UTILITIES_H__
