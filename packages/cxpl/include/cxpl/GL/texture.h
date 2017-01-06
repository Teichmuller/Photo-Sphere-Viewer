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
            static Texture *FromImage(shared_ptr<Image> image)
            {
                Texture *ret = new Texture();
                glGenTextures(1, &(ret->m_id));
                glBindTexture(GL_TEXTURE_2D, ret->m_id);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->GetWidth(), image->GetHeight(), 0, GL_BGRA, GL_UNSIGNED_BYTE, image->GetBytes());
                glBindTexture(GL_TEXTURE_2D, 0);
                return ret;
            }
            GLuint GetID() {return m_id;}
            operator GLuint() const {return m_id;}
            ~Texture()
            {
                glDeleteTextures(1, &m_id);
            }
        private:
            Texture() {}
            GLuint m_id;
        };
    }
}

#endif
