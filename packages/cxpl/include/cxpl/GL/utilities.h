#ifndef CXPL_GL_UTILITIES_H_
#define CXPL_GL_UTILITIES_H_

#include <iostream>
#include <memory>
#include <FreeImage.h>
#include <GL/glew.h>

#include <cxpl/Core/ErrorHandler.h>

using namespace std;

namespace cxpl
{
	class Image
	{
	public:
		GLubyte *GetBytes() {return m_bytes;}
        size_t GetWidth() {return m_width;}
        size_t GetHeight() {return m_height;}
		static string GetErrorMessage() {return m_errorMsg;}
        static shared_ptr<Image> ReadImage(const string &filename)
		{
			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
            shared_ptr<Image> ret(new Image);

			fif = FreeImage_GetFileType(filename.data(), 0);
			if (fif == FIF_UNKNOWN)
			{
				fif = FreeImage_GetFIFFromFilename(filename.data());
            }
            CHECK_MSG_RET_NULLPTR(fif != FIF_UNKNOWN, "Unknown file type")

			if (FreeImage_FIFSupportsReading(fif))
			{
				FIBITMAP *tmp = FreeImage_Load(fif, filename.data());
				ret->m_dib = FreeImage_ConvertTo32Bits(tmp);
				FreeImage_Unload(tmp);
			}
            CHECK_MSG_RET_NULLPTR(ret->m_dib != nullptr, "Obtaining DIB failed")

			ret->m_bytes = FreeImage_GetBits(ret->m_dib);
			ret->m_width = FreeImage_GetWidth(ret->m_dib);
            ret->m_height = FreeImage_GetHeight(ret->m_dib);
            CHECK_MSG_RET_NULLPTR((ret->m_bytes != 0) && (ret->m_width != 0) && (ret->m_height != 0), "Unknown image size")

			return ret;
		}
        virtual ~Image()
		{
			FreeImage_Unload(m_dib);
		}
	private:
        Image() {m_dib = nullptr;}
		GLubyte *m_bytes;
        FIBITMAP *m_dib;
		static string m_errorMsg;
        size_t m_width, m_height;
    };
}

#endif
