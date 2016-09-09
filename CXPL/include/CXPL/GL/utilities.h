#ifndef __CXPL_GL_UTILITIES_H__
#define __CXPL_GL_UTILITIES_H__

#include <iostream>
#include <FreeImage.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

namespace CXPL
{
	class Image
	{
	public:
		GLubyte *GetBytes() {return m_bytes;}
		GLsizei GetWidth() {return m_width;}
		GLsizei GetHeight() {return m_height;}
		static string GetErrorMessage() {return m_errorMsg;}
		static Image *ReadImage(const string &filename)
		{
			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
			Image *ret = new Image;
			fif = FreeImage_GetFileType(filename.data(), 0);
			if (fif == FIF_UNKNOWN)
			{
				fif = FreeImage_GetFIFFromFilename(filename.data());
			}
			if (fif == FIF_UNKNOWN)
			{
				m_errorMsg = "Unknown file type";
				return nullptr;
			}
			if (FreeImage_FIFSupportsReading(fif))
			{
				FIBITMAP *tmp = FreeImage_Load(fif, filename.data());
				ret->m_dib = FreeImage_ConvertTo32Bits(tmp);
				FreeImage_Unload(tmp);
			}
			if (!ret->m_dib)
			{
				m_errorMsg = "Obtaining DIB failed";
				return nullptr;
			}

			ret->m_bytes = FreeImage_GetBits(ret->m_dib);
			ret->m_width = FreeImage_GetWidth(ret->m_dib);
			ret->m_height = FreeImage_GetHeight(ret->m_dib);

			if ((ret->m_bytes == 0) || (ret->m_width == 0) || (ret->m_height == 0))
			{
				m_errorMsg = "Unknown image size";
				return nullptr;
			}

			return ret;
		}
		~Image()
		{
			FreeImage_Unload(m_dib);
		}
	private:
		Image() {}
		GLubyte *m_bytes;
		FIBITMAP *m_dib = 0;
		static string m_errorMsg;
		GLsizei m_width, m_height;
	};

	//template <class T>
	//class Rectangle
	//{
	//public:
	//    Rectangle(T x, T y, T w, T h)
	//    : m_leftbottomX(x), m_leftbottomY, m_width(w), m_height(h) {}
	//    T GetX() {return m_leftbottomX;}
	//    T GetY() {return m_leftbottomY;}
	//    T GetWidth() {return m_width;}
	//    T GetHeight() {return m_height;}
	//private:
	//    T m_leftbottomX, m_leftbottoomY, m_width, m_height;
	//};
}

#endif
