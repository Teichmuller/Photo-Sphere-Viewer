#ifndef CXPL_GL_TEXTURE_H_
#define CXPL_GL_TEXTURE_H_

#include <GL/glew.h>
#include <cxpl/GL/utilities.h>

namespace cxpl
{
    namespace GL
    {
        class Texture
        {
        public:
            static shared_ptr<Texture> FromImage(shared_ptr<Image> image)
            {
                CHECK_MSG_RET_NULLPTR(image != nullptr, "Image cannot be nullptr")
                shared_ptr<Texture> ret(new Texture());
                glGenTextures(1, &(ret->m_id));
                CHECK_MSG_RET_NULLPTR(ret->m_id != 0, "genTexture failed")
                glBindTexture(GL_TEXTURE_2D, ret->m_id);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->GetWidth(), image->GetHeight(), 0, GL_BGRA, GL_UNSIGNED_BYTE, image->GetBytes());
                glBindTexture(GL_TEXTURE_2D, 0);
                ret->m_width = image->GetWidth();
                ret->m_height = image->GetHeight();
                return ret;
            }
            GLuint GetID() const {return m_id;}
            operator GLuint() const {return m_id;}
            size_t GetWidth() const {return m_width;}
            size_t GetHeight() const {return m_height;}
            ~Texture()
            {
                glDeleteTextures(1, &m_id);
            }
        private:
            Texture() {}
            GLuint m_id;
            size_t m_width, m_height;
        };
    }
}

#endif
