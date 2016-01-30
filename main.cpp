/// https://developers.google.com/streetview/spherical-metadata
#include "XMP_config.h"
#include "utilities.h"


void Terminate()
{
    SXMPFiles::Terminate();
	SXMPMeta::Terminate();
}



int main(int argc, char **argv)
{
    GLOBALEXAM(SXMPMeta::Initialize(), "XMPMeta initialize failed!", Terminate);
    GLOBALEXAM(SXMPFiles::Initialize(), "XMPFiles initialize failed!", Terminate);
    SXMPFiles xmp_file;
    SXMPMeta xmp_meta;
    string test_file_name = "../assets/PhotoSphereTestImage.jpg";
    if (!xmp_file.OpenFile(test_file_name, kXMP_UnknownFile, kXMPFiles_OpenForRead | kXMPFiles_OpenUseSmartHandler))
    {
        if (!xmp_file.OpenFile(test_file_name, kXMP_UnknownFile, kXMPFiles_OpenForUpdate | kXMPFiles_OpenUsePacketScanning))
        {
            GLOBALEXAM(false, "Cannot open " + test_file_name + "!", Terminate);
        }
    }
    xmp_file.GetXMP(&xmp_meta);

    for (auto i : PhotoSphereProperties)
    {
        switch (i.Type)
        {
        case Bool:
            {
                bool bvalue;
                if (xmp_meta.GetProperty_Bool(PhotoSphereURI.data(), i.Name.data(), &bvalue, nullptr))
                    cout << i.Name << ": " << (bvalue ? "true" : "flase") << endl;
                else if (!i.IsRequired)
                    cout << i.Name << " doesn't exist but is not required!" << endl;
                else
                    cout << i.Name << " doesn't exist!" << endl;
                break;
            }
        case Int:
            {
                XMP_Int32 ivalue;
                if (xmp_meta.GetProperty_Int(PhotoSphereURI.data(), i.Name.data(), &ivalue, nullptr))
                    cout << i.Name << ": " << ivalue << endl;
                else if (!i.IsRequired)
                    cout << i.Name << " doesn't exist but is not required!" << endl;
                else
                    cout << i.Name << " doesn't exist!" << endl;
                break;
            }
        case Float:
            {
                double fvalue;
                if (xmp_meta.GetProperty_Float(PhotoSphereURI.data(), i.Name.data(), &fvalue, nullptr))
                    cout << i.Name << ": " << fvalue << endl;
                else if (!i.IsRequired)
                    cout << i.Name << " doesn't exist but is not required!" << endl;
                else
                    cout << i.Name << " doesn't exist!" << endl;
                break;
            }
        case Date:
            {
                XMP_DateTime tvalue;
                if (xmp_meta.GetProperty_Date(PhotoSphereURI.data(), i.Name.data(), &tvalue, nullptr))
                    cout << i.Name << ": " << tvalue << endl;
                else if (!i.IsRequired)
                    cout << i.Name << " doesn't exist but is not required!" << endl;
                else
                    cout << i.Name << " doesn't exist!" << endl;
                break;
            }
        default:
            cout << i.Name << " is unhandled type!" << endl;
        }
    }

    Terminate();
    return 0;
}

