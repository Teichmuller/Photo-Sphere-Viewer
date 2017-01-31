/// Reference: https://developers.google.com/streetview/spherical-metadata
#ifndef __PHOTOSPHEREVIEWER_PHOTOSPHERE_H__
#define __PHOTOSPHEREVIEWER_PHOTOSPHERE_H__

#include <PhotoSphereProperty.h>

#include <fstream>
#include <string>
#include <vector>
#include <CXPL/GL/buffer.h>
#include <CXPL/GL/shader.h>
#include <CXPL/GL/texture.h>
#include <CXPL/GL/utilities.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;
using namespace CXPL;

namespace PhotoSphereViewer
{
    class PhotoSphere
    {
    public:
        static shared_ptr<PhotoSphere> FromFile(const string &filename, uint32_t hslice = 25, uint32_t vslice = 25);
        void Draw();
        Shader GetShader();
        ~PhotoSphere();
    private:
    /// Constants
        const static string m_VertexShaderString;
        const static string m_FragmentShaderString;
    /// Variables
        shared_ptr<PhotoSphereProperty> m_property;
        Shader *m_shader;
        VertexArrayObject *m_vao;
        BufferObject *m_vbo;
        BufferObject *m_tbo;
        BufferObject *m_ibo;
        Texture *m_texture;

        void GenerateSphere(uint32_t hslice, uint32_t vslice, vector<vec3> &vertices, vector<vec3> &texCoord, vector<GLuint> &indices);

        void Dispose();
        PhotoSphere();
    };
}

#endif // __PHOTOSPHERE_H__
